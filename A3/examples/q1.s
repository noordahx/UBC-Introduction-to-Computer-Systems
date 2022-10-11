# Instruction area
.pos 0x100
	# p = z[7] to assembly
	ld $p, r0			# r0 = address of p
	ld $z, r1			# r1 = address of z
	ld $0x7, r2			# r2 = 7
	ld (r1, r2, 4), r2	# r2 = z[7]
	st r2, (r0)			# p = z[2]
	
	# p = z[p] to assembly
	ld (r0), r2			# r2 = p
	ld (r1, r2, 4), r2 	# r2 = z[p]
	st r2, (r0)			# p = z[p]

	# e = &m
	ld $m, r0			# r0 = addresso of m
	ld $e, r1 			# r1 = address of 
	st r0, (r1)			# e = address of m

	# *e = 1
	ld $e, r0			# r0 = address of e pointer
	ld $0x1, r1			# r1 = 1
	ld (r0), r0			# r0 = address of content of e
	st r1, (r0)			# *e = r1

	# e = &z[z[6]]
	ld $z, r0			# r0 = address of z
	ld $0x6, r1			# r1 = 6
	ld (r0, r1, 4), r1	# r1 = z[6]
	shl $2, r1			# r1 *=4
	add r1, r0			# r0 = &z[z[6]]
	ld $e, r2			# r2 = address of e
	st r0, (r2)

	# *e = *e + z[8]
	ld $z, r0			# r0 = address of z
	ld $0x8, r1			# r1 = 8
	ld (r0, r1, 4), r1	# r1 = z[8]
	ld $e, r2			# r2 = address of e
	ld (r2), r2 		# r2 = address of content of e
	ld (r2), r3			# r3 = content of e (*e)
	add r3, r1			# r3 = *e + z[8]
	st r1, (r2)			# *e = *e + z[8]
	
	halt
# Data area
.pos 0x400
p:	.long 0				# p
m:	.long 0				# m
e:	.long 0				# e
z:	.long 0				# z[0]
	.long 4				# z[1]
	.long 3				# z[2]
	.long 0				# z[3]
	.long 0				# z[4]
	.long 0				# z[5]
	.long 1				# z[6]
	.long 2				# z[7]
	.long 5				# z[8]
	.long 0				# z[9]
