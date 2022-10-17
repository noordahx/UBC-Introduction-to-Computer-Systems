.pos 0x1000
code:
# v0 = s.x[i]
        ld $s, r0           # r0 = address of s
        ld $i, r1           # r1 = address of i
        ld (r1), r1         # r1 = i
        ld $v0, r2          # r2 = address of v0
        ld (r0, r1, 4), r3  # r3 = s.x[i]
        st r3, (r2)         # v0 = s.x[i]

# v1 = s.y[i]
        ld $s, r0           # r0 = address of s
        ld $0x2, r1         # r1 = 2
        ld (r0, r1, 4), r1  # r1 = s.y[0]
        ld $i, r2           # r2 = address of i
        ld (r2), r2         # r2 = i
        ld (r1, r2, 4), r3  # r3 = s.y[i]
        ld $v1, r4          # r4 = address of v1
        st r3, (r4)         # v1 = s.y[i]

# v2 = s.z->x[i];
        ld $s, r0           # r0 = address of s
        ld $0x3, r1         # r1 = 3
        ld (r0, r1, 4), r0  # r0 = address of s_z
        ld $i, r2           # r2 = address of r2
        ld (r2), r2         # r2 = i
        ld (r0, r2, 4), r3  # r3 = s.z->x[i]
        ld $v2, r4
        st r3, (r4)

# v3 = s.z->z->y[i];
        ld $s, r0           # r0 = address of s
        ld $0x3, r1         # r1 = 3
        ld (r0, r1, 4), r0  # r0 = address of s_z
        ld (r0, r1, 4), r0  # r0 = address of s_z_z
        ld $0x2, r1         # r1 = 2
        ld (r0, r1, 4), r0  # r0 = address of s_z_z_y
        ld $i, r2           # r2 = address of i
        ld (r2), r2         # r2 = i
        ld (r0, r2, 4), r3  # r3 = s.z->z->y[i]
        ld $v3, r4
        st r3, (r4)

        halt
.pos 0x2000
static:
i:      .long 1
v0:     .long 0
v1:     .long 0
v2:     .long 0
v3:     .long 0
s:      .long 0         # x[0]
        .long 2         # x[1]
        .long s_y       # y pointer
        .long s_z       # z pointer


.pos 0x3000
heap:
s_y:    .long 0         # s.y[0]        0x3000
        .long 3         # s.y[1]        
s_z:    .long 0         # x[0]          0x3008
        .long 4         # x[1]
        .long 0         # *y
        .long s_z_z     # *z
s_z_z:  .long 0         # x[0]          0x3018
        .long 0         # x[1]
        .long s_z_z_y   # *y
        .long 0         # *z
s_z_z_y:.long 0         # y[0]          0x3028
        .long 5         # y[1]

