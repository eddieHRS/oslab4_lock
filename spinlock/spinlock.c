#include "xchg.c"

// 0 -> lock is free, 1 -> held
typedef struct __lock_t 
{ 
	int flag; 
} spinlock_t;

void spinlock_init(spinlock_t *mutex) {
	mutex->flag = 0;
}

void spinlock_acquire(spinlock_t *mutex) {
	while (xchg(&mutex->flag, 1)== 1){
	};
}

void spinlock_release(spinlock_t *mutex) {
	mutex->flag = 0;
}

