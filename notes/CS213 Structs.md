# Lecture 7
## Runtime allocation of dynamic struct

```C
struct D{
	int e;
	int f;
}
struct D* d1;
void foo() {
	d1 = malloc(sizeof(struct D));
}
```
* pointer d1 = static;
* struct iteslf is dynamic

## Struct access
* Struct members can be accessed using **offset** from base address
* Example:
	```asm
	ld 4(r0), r1  # r1 = d0.f
	st r1, (r0)   # d0.e = d0.f = f1  
	```
* Example:
	```asm
	ld $0x1000, r0   # r0 = address of d1
	ld (r0), r1      # r1 = address of struct
	ld 4(r1), r2     # r2 = d1->f
	st r2, (r1)      # d1->e = d1->f
 	```

## Variations in strcut declaration

```C
	struct D {
		int e;
		int f;
	}

e - 4 bytes
f - 4 bytes

	struct X {
		int i;
		struct D d;
		int j;
	}
i - 4 bytes
f - 4 bytes
D - 8 bytes
j - 4 bytes

	struct Y {
		int i;
		struct D *d;
		int j;
	}
i - 4 bytes
d - 4 bytes pointer
j - 4 bytes

	struct Z {
		int i;
		struct Z* z;
		int j;
	}
i - 4 bytes
z - 4 bytes pointer
j - 4 bytes

	struct W {
		int i;
		int a[10]; //actually stored in struct
		int j;
	}

i - 4 bytes
a - 20 bytes
j - 4 bytes

	struct U {
		int i;
		int *a; // points to the array outside
		int j;
	}
i - 4 bytes
a - 4 bytes pointer
j - 4 bytes
```


## Strcut size and alighnment

```C
struct X {
	char a; // 1 byte
	char b; // 1 byte
			// 2 bytes padding
	int i;  // 4 bytes
}
```
```C
struct Y {
	char a; // 1 byte
			// 3 bytes padding
	int i;  // 4 bytes
	char b; // 1 byte
			// 3 bytes padding
}
```
## Arrays of structs
```C
struct X {
	 int i;
	 int j;
	 int k;
}

struct X a[10]; //array of structures
struct X* b[10]; // array of pointers to structs
...
a[3].i // struct arrays, accessing the value of the struct variable 
b[5]->j // b[] is arrays of pointers, b[n]->j accessing the value of struct that pointer points to
```

