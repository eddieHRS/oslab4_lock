#include <stdlib.h>
#include <stdio.h>
#include "mutex.c"
#include "list.h"



void list_init(list_t* L){
	mutex_init(&L->lock);
	L->head = NULL;
}

void list_insert(list_t* L, unsigned int key){
	node_t* new = malloc(sizeof(node_t));
	if(new == NULL){
		perror("malloc");
		mutex_release(&L->lock);
		return;
	}
	new->key = key;
	//lock critical section
	mutex_acquire(&L-> lock);
	new->next = L->head;
	L->head = new;
	mutex_release(&L->lock);
	return ;
}


void list_delete(list_t* L,unsigned int key){
	
	node_t* curr = L->head;
	node_t* pre_curr = NULL;
	if(curr == NULL){
		return;
	}
	//key is head
	mutex_acquire(&L->lock);
	if(curr->key == key){
		L->head = L->head->next;
		mutex_release(&L->lock);
		return;
	}
	while(curr){
		if(curr->key == key){
			pre_curr -> next = curr->next;
			free(curr);
			mutex_release(&L->lock);
			return;
		}
		pre_curr = curr;
		curr = curr -> next;
	}
	mutex_release(&L->lock);
	return;

}

void * list_lookup(list_t* L,unsigned int key){
	node_t* result = NULL;
	mutex_acquire(&L->lock);
	node_t* curr = L->head;
	while(curr){
		if(curr->key == key){
			result = curr;
			mutex_release(&L->lock);
			break;
		}
		curr = curr -> next;
	}
	mutex_release(&L->lock);
	return result;
}



