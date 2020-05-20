#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H
#include "lib/user/syscall.h"
void syscall_init (void);

/************************/

void check_vaddr(const void*, int);

void halt(void);
void exit(int status);
pid_t exec(const char *file);
int wait(pid_t);
int read(int fd, void *buffer, unsigned length);
int write(int fd, const void* buffer, unsigned length);
int fibonacci(int);
int sum_of_four_int(int, int, int, int);

bool create (const char*file, unsigned initial_size);
int open(const char* file);
int filesize(int fd);
void seek(int fd, unsigned position);
unsigned tell(int fd);
void close(int fd);
bool remove(const char* file);

/*************************/
#endif /* userprog/syscall.h */
