#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "threads/synch.h"
#include "userprog/process.h"
#include "devices/input.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/off_t.h"
static void syscall_handler (struct intr_frame *);
struct lock file_lock;
void
syscall_init (void) 
{
  lock_init(&file_lock);
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}


void check_vaddr(const void* addr, int cnt){
	int i, j = 0;

	for(i = 0; i < cnt; i++, j += 4){
		if(!is_user_vaddr(addr + j)) exit(-1);
	}
}
void check_file_null(const char*file){
	if(file==NULL)exit(-1);
}
void check_fd_null(struct file *fp){
	if(fp==NULL)exit(-1);
}
static void
syscall_handler (struct intr_frame *f) 
{
//	hex_dump(f->esp, f->esp, 100, 1);
//	printf("\n\n%X\n\n", (uint32_t*)(f->esp));
	switch(*(uint32_t *)(f->esp)){
	  case SYS_HALT:
		  halt();
		  break;
	  case SYS_EXIT:
		  check_vaddr(f->esp + 4, 1);
		  exit(*(uint32_t*)(f->esp + 4));
		  break;
	  case SYS_EXEC:
		  check_vaddr(f->esp + 4, 1);
		  f->eax = exec((const char*)*(uint32_t*)(f->esp + 4));
		  break;
	  case SYS_WAIT:
		  check_vaddr(f->esp + 4, 1);
	          f->eax = wait((pid_t)*(uint32_t *)(f->esp + 4));
		  break;
	  case SYS_READ:
		  check_vaddr(f->esp + 4, 3);
	  	  f->eax = read((int)*(uint32_t*)(f->esp + 4), (void*)*(uint32_t*)(f->esp + 8), (unsigned)*((uint32_t*)(f->esp + 12)));
		  break;
	  case SYS_WRITE:
		  check_vaddr(f->esp + 4, 3);
		  f->eax = write((int)*(uint32_t*)(f->esp + 4), (void*)*(uint32_t*)(f->esp + 8), (unsigned)*((uint32_t *)(f->esp + 12)));
		  break;
	  case SYS_SUM:
		  check_vaddr(f->esp+4, 4);
		  f->eax = sum_of_four_int((int)*(uint32_t*)(f->esp+4),(int)*(uint32_t*)(f->esp+8), (int)*(uint32_t*)(f->esp+12), (int)*(uint32_t*)(f->esp+16));
		  break;
          case SYS_FIBO:
		  check_vaddr(f->esp+4, 1);
		  f->eax = fibonacci((int)*(uint32_t*)(f->esp+4));
		  break;
	  case SYS_CREATE:
		  check_vaddr(f->esp + 4, 2);
		  f->eax = create((const char*)*(uint32_t*)(f->esp + 4), (unsigned)*(uint32_t*)(f->esp + 8));
		  break;
      case SYS_REMOVE:
		  check_vaddr(f->esp + 4, 1);
		  f->eax = remove((const char*)*(uint32_t*)(f->esp + 4));
		  break;
	  case SYS_OPEN:
		  check_vaddr(f->esp + 4, 1);
		  
		  f->eax = open((const char*)*(uint32_t*)(f->esp + 4));
		  break;
	  case SYS_CLOSE:
		  check_vaddr(f->esp + 4, 1);
		  close((int)*(uint32_t*)(f->esp + 4));
		  break;
	  case SYS_FILESIZE:
		  check_vaddr(f->esp + 4, 1);
		  f->eax = filesize((int)*(uint32_t*)(f->esp + 4));
		  break;
	  case SYS_SEEK:
		  check_vaddr(f->esp + 4, 2);
		  seek((int)*(uint32_t*)(f->esp + 4), (unsigned)*(uint32_t*)(f->esp + 8));
		  break;
	  case SYS_TELL:
		  check_vaddr(f->esp + 4, 1);
		  f->eax = tell((int)*(unsigned*)(f->esp + 4));
		  break;
  }
}

int sum_of_four_int(int a, int b, int c, int d){
	return (a+b+c+d);
}

int fibonacci(int n){
	int i;
	int a = 1;
	int b = 1;
	int c;
	if(n==1)return 1;
	if(n==2)return 1;
	for(i = 0; i<n-2; i++){
		c = a+b;
		a = b;
		b = c;
	}
	return c;
}

void halt(void){
	shutdown_power_off();
}

void exit(int status){
	int i;
	struct thread *cur;
	cur = thread_current();
	printf("%s: exit(%d)\n", cur->name, status);
	cur->exit_status = status;
	
	for(i = 2; i < FDNUM; i++){
		if(cur->fd[i]==NULL){
			continue;
		}
		else if(cur->fd[i] != NULL){
			close(i);
		}
	}

	thread_exit();
}

pid_t exec(const char *file){
	return process_execute(file);
}

int wait(pid_t pid){
	return process_wait(pid);
}

int read(int fd, void* buffer, unsigned length){
	int i, result;

	uint8_t temp = 0;
	struct file* fp;
//	lock_acquire(&file_lock);
	check_vaddr(buffer, 1);
	lock_acquire(&file_lock);
	if(fd == 0){
		for(i = 0; i < length; i++){
		//	temp = input_getc();
			*((uint8_t*)(buffer+i)) = input_getc();
		}
		if(i!=(int)length)
			result = -1;
		else
			result = length;
	}
	else if(fd==1){
		lock_release(&file_lock);
		exit(-1);	
	}
	else{
		fp = thread_current()->fd[fd];
		
		check_fd_null(fp);
	//	lock_acquire(&file_lock);
		result = file_read(fp, buffer, length);
	//	lock_release(&file_lock);
	}
	lock_release(&file_lock);
	return result;
}

int write(int fd, const void *buffer, unsigned length){
	int result = -1;
	struct file* fp;
//	lock_acquire(&file_lock);
	check_vaddr(buffer, 1);
	lock_acquire(&file_lock);
	if( fd == 1 ){
		putbuf(buffer, length);
		result = length;
	}
	else if(fd >= 2){
		fp = thread_current()->fd[fd];
		if(fp==NULL){
			lock_release(&file_lock);
			exit(-1);
		}
	//	lock_acquire(&file_lock);
		result = file_write(fp, buffer, length);
	//	lock_release(&file_lock);
	}
	lock_release(&file_lock);
	return result;
}

bool create(const char* file, unsigned initial_size){
	check_file_null(file);	
	check_vaddr(file, 1);
	return filesys_create(file, initial_size);
}

bool remove(const char* file){
	check_file_null(file);
	check_vaddr(file, 1);
	return filesys_remove(file);
}	

int filesize(int fd){
	struct file* fp;
	fp = thread_current()->fd[fd];
	
	check_fd_null(fp);
	return file_length(fp);
}

int open(const char* file){
	int i;
	int result = -1;
	check_file_null(file);
//	struct file*fp = filesys_open(file);
	struct thread *t = thread_current();
//	check_file_null(file);
	check_vaddr(file, 1);
	lock_acquire(&file_lock);
	struct file* fp = filesys_open(file);
	if(fp == NULL) result = -1;
	else {
	//	lock_acquire(&file_lock);
		if(strcmp(t->name, file)==0){
			file_deny_write(fp);
		}
		for(i = 2; i < FDNUM; i++){
			if(t->fd[i] == NULL){
				t->fd[i] = fp;
				result = i;
				break;
			}
		}
	}
	lock_release(&file_lock);
	return result;
}

unsigned tell(int fd){
	struct file *fp;
	fp = thread_current()->fd[fd];
	check_fd_null(fp);
	return file_tell(fp);
}

void seek(int fd,unsigned position){
	struct file *fp;
	fp = thread_current()->fd[fd];

	check_fd_null(fp);
	file_seek(fp, position);
}

void close(int fd){
	struct file *fp;
	fp = thread_current()->fd[fd];
	thread_current()->fd[fd] = NULL;
	file_close(fp);
}
