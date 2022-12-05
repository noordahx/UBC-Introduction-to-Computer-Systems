# Structs 2
# Dynamic allocation in C and Java
* Programs can allocate memory dynamically
	* allocation reserves a range of memory for a purpose
* In java, instances of classes are allocated by the *new* keyword
* In C, byte ranges are allocated by call to *malloc* procedure
	* these bytes can be used for *any type* that can fit in them

* Memory allocation:

```cpp
void* malloc(unsigned long n);
```

* n is the number of bytes to allocate
* return tupe is void*
	* a pointerto anything (no specific type assigned)
	* can be cast to/from any other pointer type
	* cannot be dereferenced directly

* Use *sizeof* to determine the number of bytes to allocate
	* *sizeof(x)* statically computes the # of bytes in a type or variable
	* caution: *sizeof(x)* (pointer) gives the size of a *pointer*, not what it points to
```cpp
struct Foo* f = malloc(sizeof(*f)); // return the size of pointer = 4
```

## Memery deallocation
* Wise managemen of memory requires *deallocation*
	* memory is a finite resourse
	* deallocation frees previously allocated memory for re-use
* In Java:
	* automatic garbage collection: requires keeping track of every reference to an object
* In C:
	* Dynamic memory must be deallocated by calling *free*
	* *free* deallocates memory immediately; does not check to see if it is still in use
* **Memory leak**:
	* When dynamically allocated data is not deallocated when it is no longer needed
	* size of program gradually increases; available memory leaks away

## Memory heap
* The *heap* is a large section of memory from which *malloc* allocates objects
	* *malloc* finds unused space in the heap, marks the chunk of bytes as used, and returns the address of the first byte
	* *free* marks the previously allocated chunck of bytes as unused
* In Java: all objects are stored on the heap

## Issues with explicit deallocation
* What *free(x)* does
	* deallocates "object" at address x
	* this memory can be reused by subsequent call to malloc
* What *free(x)* des not do
	* it does not change the value of x
	* other variables may still point there too 
	* the binary data stored at address x is not erased
