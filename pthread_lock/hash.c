#include "list.c"
#include "hash.h"


void hash_init(hash_t * H){
	int i;
	for(i = 0; i < BUCKETS; i++){
		list_init(&H->lists[i]);
	}
}

void hash_insert(hash_t* H,int key){
	int bucket = key % BUCKETS;
	list_insert(&H->lists[bucket],key);
}

void* hash_lookup(hash_t * H,int key){
	int bucket = key % BUCKETS;
	return list_lookup(&H->lists[bucket],key);
}

void hash_delete(hash_t* H,int key){
	int bucket = key % BUCKETS;
	list_delete(&H->lists[bucket],key);
}
