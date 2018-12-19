/*
classical counter using pthread
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "mutex.c"

typedef struct __counter_t
{
	mutex_t lock;
	int value;

} counter_t;

void counter_init(counter_t *c,int value){
	c -> value = value;
	mutex_init(&c->lock);
}

int counter_get_value(counter_t* c){
	mutex_acquire(&c->lock);
	int rc = c -> value;
	mutex_release(&c->lock);
	return rc;
}

void counter_increment(counter_t *c){
	mutex_acquire(&c->lock);
	c -> value++;
	mutex_release(&c->lock);
}

void counter_decrement(counter_t *c){
	mutex_acquire(&c->lock);
	c -> value--;
	mutex_release(&c->lock);
}
