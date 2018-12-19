#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <time.h>
#include <sys/mman.h>
#define errExit(msg)
#include "sys_futex.c"
#include "mutex.h"




void mutex_init(mutex_t *lock)
{
	lock -> futex = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_SHARED,-1,0);
	*(lock -> futex) = 0;
	//0 for available
	//1 for unavailable
}


void mutex_acquire(mutex_t *lock) {
	int s;
	int a = random();
	while(1){
		//printf("i am in mutex_acquire\n");
		if(__sync_bool_compare_and_swap(lock->futex,0, 1))
			break;
		s = sys_futex(lock->futex,FUTEX_WAIT,1,NULL,NULL,0);
		// if(errno == EAGAIN)
		//     printf("EAGAIN %d %d\n",a,s);
		if(s == -1 && errno != EAGAIN)
			errExit("futex-FUTEX_WAIT");
	}
	
}


void mutex_release(mutex_t *lock) {
	int s;
	if(__sync_bool_compare_and_swap(lock->futex,1,0))
		s = sys_futex(lock->futex,FUTEX_WAKE,1,NULL,NULL,0);
	// if(s != 0)
	// 	printf("wake %d\n",s);
		if(s == -1)
			errExit("futex-FUTEX_WAKE");

}
