# Memory allocation
## Memory heap
* The **heap** is a large section of memory from which **malloc** allocates objects
	* **malloc** finds unused space in the help, marks the chunk of bytes as used, and returns the address of the first byte
	* **free** marks the previously allocated chunk of bytes as unused
* In java: all objects are stored on the heap

