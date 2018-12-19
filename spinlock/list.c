#include "spinlock.c"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>


void list_init(list_t* L){
	spinlock_init(&(L->lock));
	L->head = NULL;
}

void list_insert(list_t* L, unsigned int key){
	node_t* new = malloc(sizeof(node_t));
	if(new == NULL){
		perror("malloc");
		spinlock_release(&(L->lock));
		return;
	}
	new->key = key;
	//lock critical section
	spinlock_acquire(&L-> lock);
	new->next = L->head;
	L->head = new;
	spinlock_release(&(L->lock));
	return ;
}


void list_delete(list_t* L,unsigned int key){
	node_t* curr = L->head;
	node_t* pre_curr = NULL;
	//key is head
	if(curr == NULL){
		return;
	}
		
	spinlock_acquire(&(L->lock));
	if(curr->key == key){
		L->head = L->head->next;
		spinlock_release(&(L->lock));
		return;
	}
	while(curr){
		if(curr->key == key){
			pre_curr -> next = curr->next;
			free(curr);
			spinlock_release(&(L->lock));
			return;
		}
		pre_curr = curr;
		curr = curr -> next;
	}
	spinlock_release(&(L->lock));
	return;

}

void * list_lookup(list_t* L,unsigned int key){
	node_t* result = NULL;
	spinlock_acquire(&(L->lock));
	node_t* curr = L->head;
	while(curr){
		if(curr->key == key){
			result = curr;
			spinlock_release(&(L->lock));
			break;
		}
		curr = curr -> next;
	}
	spinlock_release(&(L->lock));
	return result;
}



