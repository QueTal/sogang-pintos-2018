#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "userprog/process.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}


void check_vaddr(const void* addr, int cnt){
	int i, j = 0;

	for(i = 0; i < cnt; i++, j += 4){
		if(!is_user_vaddr(addr + j)) exit(-1);
	}
}


static void
syscall_handler (struct intr_frame *f) 
{
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
	printf("%s: exit(%d)\n", thread_current()->name, status);
	thread_current()->exit_status = status;
	thread_exit();
}

pid_t exec(const char *file){
	return process_execute(file);
}

int wait(pid_t pid){
	return process_wait(pid);
}

int read(int fd, void* buffer, unsigned length){
	int i;
	char *buffer2 = (char*)buffer;
	uint8_t temp = 0;
	if(fd == 0){
		for(i = 0; i < (int)length; i++){
			temp = input_getc();
			buffer2[i] = (char)temp;
			if(buffer2[i]=='\0')return i;
		}
	}
	return -1;
}

int write(int fd, const void *buffer, unsigned length){
	if( fd == 1 ){
		putbuf(buffer, length);
		return length;
	}
	return -1;
}

