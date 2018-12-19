/*
classical counter using spinlock
*/
#include <stdlib.h>
#include <stdio.h>
#include "spinlock.c"
#include "counter.h"

void counter_init(counter_t *c,int value){
	c -> value = value;
	spinlock_init(&c->lock);
}

int counter_get_value(counter_t* c){
	spinlock_acquire(&c->lock);
	int rc = c -> value;
	spinlock_release(&c->lock);
	return rc;
}

void counter_increment(counter_t *c){
	spinlock_acquire(&c->lock);
	c -> value++;
	spinlock_release(&c->lock);
}

void counter_decrement(counter_t *c){
	spinlock_acquire(&c->lock);
	c -> value--;
	spinlock_release(&c->lock);
}
