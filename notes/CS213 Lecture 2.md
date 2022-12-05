	# CS221 Lecture 2
## Big-endian vs Little-endian
### Big-endian
* The first byth stored is the most significant byte
* Used in old IBM servers, network connections
	i 0x12
	i+1 0x34
	i+2 0x56
	i+3 0x78
### Little-endian
* The first byte stored is the least significant byte
* Used in most Intel-based systems
	i 0x78
	i+1 0x56
	i+2 0x34
	i+3 0x12

### Address alignment
![[Pasted image 20220914084759.png]]

* However, forcing addresses to be aligned is better for hardware
	* Address whose numberi value is a multiple of the object size
		* it depends on the object; it gets slightly more complicated with arrays and structs
* Aligned adresses are better - smaller things fit inside larger things
	* Two shors fit inside and int, etc
	* THis is significant for arrays
* Some CPUs dont support misaligned addresses
* 