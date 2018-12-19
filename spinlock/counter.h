typedef struct __counter_t
{
	spinlock_t lock;
	int value;

} counter_t;

void counter_init(counter_t *c,int value);
int counter_get_value(counter_t* c);
void counter_increment(counter_t *c);
void counter_decrement(counter_t *c);
