#define BUCKETS 500
typedef struct __hash_t
{
	list_t lists[BUCKETS];
}hash_t;

void hash_init(hash_t * H);
void hash_insert(hash_t* H,int key);
void* hash_lookup(hash_t * H,int key);
void hash_delete(hash_t* H,int key);
