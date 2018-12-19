 #include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "mutex.c"
#include "counter.h"
#include "list.h"
#include "hash.h"
#include "sys/time.h"
#include <math.h>
#define N 1000000

int thread_count;

void* testcounter(void* rank);
void* test_list_insert(void* rank);
void* test_list_insert_and_delete(void* rank);
void* test_hash_insert(void* rank);
void* test_hash_insert_and_delete(void* rank);

counter_t* counter ;
list_t* list;
hash_t* hash;

int main(int argc,char* argv[])
{
	struct timeval begin,end;

	counter = (counter_t*)malloc(sizeof(counter_t));
	counter_init(counter,0);
	list = (list_t*)malloc(sizeof(list_t));
	list_init(list);
	hash = (hash_t*)malloc(sizeof(hash_t));
	hash_init(hash);



	
	long thread;
	pthread_t * thread_handles;
	if(argc == 1)
		thread_count = 4;
	else
		thread_count = strtol(argv[1],NULL,10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));

	//create thread for test
	for(thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread],NULL,testcounter,(void*) thread);

	gettimeofday(&begin,NULL);
	for(thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread],NULL);
	gettimeofday(&end,NULL);

	//test for list
	node_t* re = list_lookup(list,3);
	if(re == NULL) printf("re is NULL\n");
	//test for hash
	//re = hash_lookup(hash,2);
	printf("buckets: %d\n",BUCKETS);
	if(re != NULL) printf("hash num: %d\n",re->key);
	if(end.tv_usec-begin.tv_usec < 0){
		end.tv_sec -= 1;
		end.tv_usec += 1000000;
	}

	printf("%ld s %ld ms\n",end.tv_sec - begin.tv_sec,end.tv_usec-begin.tv_usec);

	//for pthread
	//pthread_mutex_destroy(&((counter->lock).pmutex));

	free(thread_handles);
	return 0;
}

void* testcounter(void* rank){
	long my_rank = (long) rank;
	int i ;
	for(i = 0; i < N; i++)
		counter_increment(counter);
	printf("testcounter thread %ld of %d and%d i:%d\n",my_rank,thread_count,counter_get_value(counter),i);
	return NULL;
}

void* test_list_insert(void* rank){
	long my_rank = (long) rank;
	int i ;
	for(i = 0; i < N; i++)
		list_insert(list,my_rank);
	printf("test_list_insert thread %ld of %d i:%d\n",my_rank,thread_count,i);
	return NULL;
}

void* test_list_insert_and_delete(void* rank){
	long my_rank = (long) rank;
	int i;
	for(i = 0; i < N; i++){
		list_insert(list,my_rank);
		list_delete(list,my_rank);
	}
	printf("test_list_insert_and_delete thread %ld of %d i:%d\n",my_rank,thread_count,i);
	return NULL;
}

void* test_hash_insert(void* rank){
	long my_rank = (long) rank;
	int i ;
	for(i = 0; i < N; i++)
		hash_insert(hash,my_rank);
	printf("test_hash_insert thread %ld of %d i:%d\n",my_rank,thread_count,i);
	return NULL;
}

void* test_hash_insert_and_delete(void* rank){
	long my_rank = (long) rank;
	int i;
	for(i = 0; i < N; i++){
		hash_insert(hash,my_rank);
		hash_delete(hash,my_rank);
	}
	printf("test_hash_insert thread %ld of %d i:%d\n",my_rank,thread_count,i);
	return NULL;
}
