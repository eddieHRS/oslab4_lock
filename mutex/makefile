	
mymain: mymain.c  libcounter.so liblist.so libhash.so
	export LD_LIBRARY_PATH=/home/eddie/桌面/oslab5/提交内容/mutex
	gcc mymain.c -o myprogram -lcounter -llist -lhash -L. -pthread
libhash.so:hash.c hash.h
	gcc hash.c -fPIC -shared -o  libhash.so -pthread
liblist.so:list.c list.h
	gcc list.c -fPIC -shared -o  liblist.so -pthread
libcounter.so:counter.c counter.h
	gcc counter.c -fPIC -shared -o libcounter.so -pthread



