# Reference counting 13 October 2022
* refcount.h
```c
void* rc_malloc(int nbytes);
void rc_keep_ref(void* p);
void rc_free_ref(void* p);
```
* refcount.c
```c
void* rc_malloc(int nbytes){
	int* ref_count = malloc(nbytes+8);
	*ref_count = 1;
	return((void*) ref_count)+8;
}
void rc_keep_ref(void* p){
	int* ref_count = p-8;
	(*ref_count)++;
}
void rc_free_ref(void* p){
	int* ref_count = p-8;
	(*ref_count)--;
	if(*ref_count == 0)
		free(ref_count);
}
```
