# CS213 Lecture 3
## Shifting bits
### Positive values (SIGNED shifts ">>")
* Shifting left by *b* << multiplying by 2^*b*
* Shifting right by *b* >> dividing by 2^*b*

### Two's compliment (UNSIGNED shifts ">>>")
* Shifting and **cloning** the first element when shifiting - **Sign extending**

### Example
* 47 (base 10) / 4 = 47 (base 10) >> 2 == 00101111 (base 2) >> 2 == 
== 00001011 (base 2) == 11 (base 10)
* 55 (base 10) == 00110111 (base 2) << 1 == 01101110 (base 2) == 110 (base 10)
* 110 (base 10) == 01101110 (base 2) << 1 == 11011100 (base 2) == two's compliment [128, -127]

## Extending integers
Extending is - increasing the number of bits (or bytes) used to store an integer
b: 1111 1010 (base 2) == 0xfa (hex)
i: 1111 .... 1111 1010 (base 2) == 0xfffffffa (hex)

#### Signed extension
* used with signed numbers (everything in Java is signed)
* copies sign bit into upper, empty bits of the extended number

#### Zero extension
* used with unsigned numbers (C)
* sets upper, empty bits to 0
* can be forced by *masking* using logical (bitwise) AND operator
` int u = b & 0xff` u: 0xfa (250)

### Truncating integers
* We can also use fewer bits to represent a value
```
int i = -6;
byte b = i;
out.printf("b: 0x%x %d, i: 0x%x %d\n", b, b, i, i);
```
* What could go wrong?
	* if i is 256, what is b? What if i is 128?
		i: 0x00000100 b: 0x00
		i: 0x00000080 b: 0x80 == -128
* Java warns you if you truncate implicitly
	* To hide warning, cast explicitly
		`byte b = (byte) i;`


# Static scalars and Arrays
## CPU instructions
**The CPU** - CPUs execute *instructions*, not C or Java code

Executeion proceeds in *stages*:
* *Fetch*: load the net instruction from memory
* *Decode*: figure out from the instruction what need to be done
* *Execute*: do what the instruction specifies

CPU instructions are very simple:
* Read (load) a value from memory
* Write (store) a value to memory
* Add/substract/AND/OR/etc. two numbers
* Shift a number
* Control flow 

Some of these operations are carried out by an ALU (Arithmetic & Logic Unit)
* ALU is used in the execute stage

## Phases of computation
1. Human creation: design program and describe it in high-level language
2. Compilation: convert  high-level human description into machine-executable text
3. Execution: a physical machine executes the code text

IDEA -> [Human creation] -> Source code -> [Compilation] -> Object code -> [Execution] -> Dynamic Code 
## Static vs dynamic computation 
* Exection
	* Parameterized by input values *unknown* at compilation
	* Producing output values that are *unknownable* at compilation 

* Anything the *compiler can compute* is called **static**
* Anything that can *only be discoverd during execution* is called **dynamic**

## The processor (CPU)
* Implements a set of *insruction*
* Each instruction is implemented using *logic gates*
	* build from *transistors*: fundatmental mechanism of computation
* Instructiond design philosiphies
	* **RISC (reduced instruction set computer)**: fewer and simpler instuctions makes processor design simpler
	* **CISC (complete instruction set computer)**: having more types of insructions (and more complex instructions) allows for shorter/simpler program code and simpler compilers


* Accessing memory is SLOW
	* ~100CPU cycles for every memory access
	* goal: fast programs that avoid accessing memory when possible
* Big instructions are costly
	* Memory addresses are big
	* Big instructions lead to big programs
	* Reading instructions from memory is slow
	* Large instructions use more CPU resources

## General purpose registers
* Register file
	* Small. fast memory stored in CPU itself
	* roughly single-cycle access
## Special purpose registers
* A special-purpose register can only be used for certain purposes
* Examples:
	* PC (program counter): contains address of next instruction to execute
	* IR (instruction register): contains the machine instruction that has just been fetched from memory
## Instruction set architecture (ISA)
* ISA is a formal interface to a proessor implementation
	* defines the instructions the processor implements
	* defines the format of each iteration
* Types of instrucitons:
	* math and logic
	* memory access
		* control transfer: goto and conditional goto

## Representing Instruciton Semantics
* RTL: simple, convenient pseydo language to describe semantics
	* easy to read/write, describes machine steps
* Syntax:
	* each line is of the form: LHS <- RHS
	* LHS is a memory or register that receives a value
	* RHS is constant, memory, register, or expression on two registers
	* m[a] is a memory in address a
	* r[i] is a register with number a
* Exampes
	* Register 0 receives 0x2000
		* r[0] <- 0x2000
	* Register 1 receives memory whose adress is in register 0
		* r[1] <- m[r[0]]
	* Register 2 is increased by the values in register 1:
		* r[2] <- r[2]+r[1]

* Variables are named storage locations for values
* Features:
	* Name
	* Type/size
	* Scope 
	* Lifetime
	* Memory location (address)
	* Value
## Static variables, built-in types
