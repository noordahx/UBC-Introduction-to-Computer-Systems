# Lecture 6
## Pointer
TYPE * p;
* stores the address of another variable
* addess the value using *dereferencing* with *
* can get the address of the integer and assign to pointer with &
* when adding 3 to an `int*` yields a pointer value 12 bytes larger than the original
* &a[7]- &a[5] == 5 will count the number of elements between 2 adresses, not the number of bytes

## Structs in C
* D.e = ptrD->e = * ptrD.e
* Dynamic struct allocation
```
struct D {
	int e;
	int f;
};

struct D* d1;
void foo(){
	d1 = malloc(sizeof(strict D));
};
```
```
0x1000: 0x2000 (address of struct)
...
0x2000: value of d1->e
0x2004: value 0f d1->f
```