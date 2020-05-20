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

/*************************/
#endif /* userprog/syscall.h */
