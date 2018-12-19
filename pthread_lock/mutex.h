typedef struct __mutex_t {
	pthread_mutex_t pmutex;
} mutex_t;

void mutex_init(mutex_t *lock);
void mutex_acquire(mutex_t *lock);
void mutex_release(mutex_t *lock);
