#include <stdio.h>
#include <syscall.h>
#include <syscall.h>
int main(int argc, char **argv){
	int fibo_result, sum_result;
	
	fibo_result = fibonacci(atoi(argv[1]));
	sum_result = sum_of_four_int(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	printf("%d %d\n", fibo_result, sum_result);
	return EXIT_SUCCESS;


}
