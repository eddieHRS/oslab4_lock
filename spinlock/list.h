typedef struct __node_t
{
	int key;
	struct __node_t* next;	
}node_t;



typedef struct __list_t
{
	spinlock_t lock;
	node_t * head;
}list_t;

void list_init(list_t* L);
void list_insert(list_t* L, unsigned int key);
void list_delete(list_t* L,unsigned int key);
void * list_lookup(list_t* L,unsigned int key);
