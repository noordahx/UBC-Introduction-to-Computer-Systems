# Instruction area
.pos 0x100
	# load adresses of variables
    ld $a, r0           # r0 = address of a
    ld $s, r1           # r1 = address of s
    ld $tos, r2         # r2 = address of tos
    ld $tmp, r3         # r3 = address of tmp


    # tmp = 0
    # tos = 0
    ld $0x0, r4         # r4 = 0
    st r4, (r3)         # tmp = 0
    st r4, (r2)         # tos = 0

    # s[tos] = a[0]
    ld (r0, r4, 4), r5  # r5 = a[0]
    st r5, (r1, r4, 4)  # s[tos] = a[0]

    # tos++
    inc r4              # r4 = 1
    st r4, (r2)         # tos = 1

    # s[tos] = a[1]
    ld (r0, r4, 4), r5  # r5= a[1]
    st r5, (r1, r4, 4)  # s[tos] = a[1]

    # tos++
    inc r4              # r4 = 2
    st r4, (r2)         # tos = 2

    # s[tos] = a[2]
    ld (r0, r4, 4), r5  # r5= a[2]
    st r5, (r1, r4, 4)  # s[tos] = a[2]

    # tos++
    inc r4              # r4 = 3
    st r4, (r2)         # tos = 3
    
    # tos--
    dec r4              # r4 = 2
    st r4, (r2)         # tos = 2
    
    # tmp = s[tos]
    st r5, (r3)

    # tos--
    dec r4              # r4 = 1
    st r4, (r2)         # tos = 1

    # tmp = tmp + s[tos]
    ld (r1, r4, 4), r6  # r6 = s[tos]
    add r6, r5          # r5 = r6 + r5
    st r5, (r3)         # tmp = tmp + s[tos]

    # tos--
    dec r4              # r4 = 0
    st r4, (r2)         # tos = 0

    ld (r1, r4, 4), r6  # r6 = s[tos]
    add r6, r5          # r5 = tmp + s[tos]
    st r5, (r3)


	halt
# Data area
.pos 0x400
a:	.long 1				# a[0]
    .long 2             # a[1]
    .long 3             # a[2]
s:	.long 0				# s[0]
    .long 0             # s[1]
    .long 0             # s[2]
    .long 0             # s[3]
    .long 0             # s[4]
tos:.long 0             # tos
tmp:.long 0             # tmp