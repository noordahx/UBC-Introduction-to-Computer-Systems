# Lecture 4
## RTL Exampes:
RTL for a=0:
	m[0x100]<-0
a=x+y;c=a;
	m[0x100]<-m[*address of X*] + m[*address of Y*]
	m[*address of C*]<-m[0x100]

## Static variable access
```
int a;
int b[10];

void foo(){
	a = 0;
	b[a] = a;
}
```
* Key observations:
	* compiler does not know address of b[a]
		* unless it knows the value of `a` statically, which it could be looking at `a=0;` , but not in general
* Array access in computed from a **base address** and **index**
	* address of element = **base + offset**; **offset = index * element size**
	* The base address (0x2000) and element size(4) are static; the **index** is dynamic
## ISA design
* ISA design goals:
	* minimize # of memory instructions in ISA
	* at most 1 memory accress per instruction
	* minimize # of total instructions in ISA
	* minimize instruction size
## Examples
m[0x1000] <- 0x0
```
	r[0] <- 0x0
	r[1] <- 0x1000
	m[r[1]] <- r[0]
```
m[0x2000 + 4 * m[0x1000]] <- m[0x1000]
```
	r[0] <- 0x1000
	r[1] <- m[r[0]]
	r[2] <- 0x2000
	m[r[2] + 4*r[1]] <- r[1] 
```
## Translating the code
TO RTL:
```
int a;
int b[10];

void foo(){
	a = 0;
	b[a] = a;
}
```

```
r[0] <- 0
r[1] <- 0x1000
m[r[1]] <- r[0]

r[2] <- m[r[1]]
r[3] <- 0x2000
m[r[3]+3*r[2]] <- r[2]
```

![[Pasted image 20220923011152.png]]

* .___ preprosesor directives (not translated to machine code)
* labels [a:] 
	* at the address .pos 0x1000 is stored a variable which is referred as **a** and it has the value 0 [.long 0]