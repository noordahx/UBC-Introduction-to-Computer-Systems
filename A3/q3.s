# Instruction area
.pos 0x100
    # a = 3
    ld $a, r0           # r0 = address of a
    ld $0x3, r1         # r1 = 3
    st r1, (r0)         # a = 3

    # p = &a
    ld $p, r1           # r1 = address of p
    st r0, (r1)         # r0 = address of a
    
    # *p = *p - 1
    ld (r1), r2         # r2 = p (address of some value)
    ld (r2), r3         # r3 = *p
    dec r3              # r3 = *p - 1
    st r3, (r2)         # *p = *p - 1

    # p = &b[0]
    ld $b, r0           # r0 = address of b[0]
    ld $p, r1           # r1 = address of p
    st r0, (r1)         # p = &b[0]

    # p++
    ld (r1), r2         # r2 = p
    inca r2              # r2 = r2 + 4
    st r2, (r1)         # p = p + 4

    # p[a] = b[a]
    ld $a, r0           # r0 = address of a[0]
    ld $b, r1           # r1 = address of b[0]
    ld $p, r2           # r2 = adress of p
    ld (r2),r2          # r2 = pointer address
    ld (r0), r3         # r3 = a
    ld (r1, r3, 4), r4  # r4 = b[a]
    st r4, (r2, r3, 4)  # p[a] = r4 = b[a]

    # *(p+3) = b[0]
    ld $p, r0           # r0 = address of p
    ld $b, r1           # r1 = address of b
    # inca r0             # r0 = r0+4
    # dec r0              # r0 = r0-1
    ld (r1), r2         # r2 = b[0]
    ld (r0), r0         # r0 = pointer address
    st r2, 0xc(r0)      # *(p+3) = b[0]

    halt


# Data area
.pos 0x400
a:  .long 0     # a
p:  .long 0     # p
b:  .long 0x0   # b[0]
    .long 0x1   # b[1]
    .long 0x2   # b[2]
    .long 0x3   # b[3]
    .long 0x4   # b[4]