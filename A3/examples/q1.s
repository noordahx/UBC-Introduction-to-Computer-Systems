.pos 0x100
	ld $p, r0			# r0 = address of p
	ld $z, r1			# r1 = address of z
	ld $e, r2			# r2 = address of e
	ld $0x7, r3			# r3 = 7
	ld (r1, r3, 4), r3	# r3 = z[7]
	st r3, (r0)			# p = z[7]
	ld (r0), r3			# r3 = p
	ld (r1, r3, 4), r3	# r3 = z[p]
	st r3, (r0)			# p = z[p]
	ld $m, r3			# r3 = address of m
	st r3, (r2)			# e = &m
	ld (r2), r5			# r2 = *e
	ld $0x1, r4			# r4 = 1
	st r4, (r5)			# *e = 1
	ld 

# Data area
.pos 0x200
p:	.long 0				# p
m:	.long 0				# m
e:	.long 0				# e
z:	.long 0				# z[0]
	.long 0				# z[1]
	.long 0				# z[2]
	.long 0				# z[3]
	.long 0				# z[4]
	.long 0				# z[5]
	.long 0				# z[6]
	.long 0				# z[7]
	.long 0				# z[8]
	.long 0				# z[9]
