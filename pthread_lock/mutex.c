#include <pthread.h>
#include "mutex.h"




void mutex_init(mutex_t *lock) {
	pthread_mutex_init(&lock->pmutex,NULL);
}


void mutex_acquire(mutex_t *lock) {
	pthread_mutex_lock(&lock->pmutex);
}


void mutex_release(mutex_t *lock) {
	pthread_mutex_unlock(&lock->pmutex);
}
