.pos 0x0
    ld   $0x1028, r5            # r5 = address of element after stack
    ld   $0xfffffff4, r0        # r0 = -12
    add  r0, r5                 # allocate 12 bytes in stack
    ld   $0x200, r0             # r0 = &arr[0]
    ld   0x0(r0), r0            # r0 = arr[0]
    st   r0, 0x0(r5)            # stack's first element is arr[0]
    ld   $0x204, r0             # r0 = &arr[1]
    ld   0x0(r0), r0            # r0 = arr[1]
    st   r0, 0x4(r5)            # stack's second element is arr[1]
    ld   $0x208, r0             # r0 = &arr[2]
    ld   0x0(r0), r0            # r0 = arr[2]
    st   r0, 0x8(r5)            # stack's third element is arr[2]
    gpc  $6, r6                 # r6 = pc + 6
    j    0x300                  # goto 0x300
    ld   $0x20c, r1             # r1 = &arr[3]
    st   r0, 0x0(r1)            # arr[3] = r0
    halt
.pos 0x200
    .long 0x13            # arr[0]
    .long 0x1            # arr[1]
    .long 0x2            # arr[2]
    .long 0x00000000            # arr[3]
.pos 0x300
    ld   0x0(r5), r0            # r0 = arr[0] = stack's first element
    ld   0x4(r5), r1            # r1 = arr[1] = stack's second element
    ld   0x8(r5), r2            # r2 = arr[2] = stack's third element
    ld   $0xfffffff6, r3        # r3 = -10
    add  r3, r0                 # r0 = arr[0] - 10
    mov  r0, r3                 # r3 = arr[0] - 10
    not  r3                     # r3 = ~r3
    inc  r3                     # r3 = -(arr[0]-10)
    bgt  r3, L6                 # if (arr[0] < 10) goto L6 (default case)
    mov  r0, r3                 # r3 = arr[0] - 10
    ld   $0xfffffff8, r4        # r4 = -8
    add  r4, r3                 # r3 = arr[0] - 18
    bgt  r3, L6                 # if (arr[0] > 18)  goto L6 (default case)
    ld   $0x400, r3             # r3 = address of jump table
    ld   (r3, r0, 4), r3        # load jmptable[arr[0] - 10]
    j    (r3)                   # goto jmptable[arr[0] - 10]
.pos 0x330
A0:
    add  r1, r2                 # r2 = arr[1] + arr[2]
    br   L7                     # goto L7   
A1:
    not  r2                     # r2 = ~r2
    inc  r2                     # r2 = -r2 = arr[2]
    add  r1, r2                 # r2 = arr[1] - arr[2]
    br   L7                     # goto L7
A2:
    not  r2                     # r2 = ~re
    inc  r2                     # r2 = -r2
    add  r1, r2                 # r2 = arr[1] - arr[2]
    bgt  r2, L0                 # if (arr[1] > arr[2]) goto L0
A3:
    ld   $0x0, r2               # r2 = 0
    br   L1                     # goto L1
L0:
    ld   $0x1, r2               # r2 = 1
L1:
    br   L7                     # goto L7
A4:
    not  r1                     # r1 = ~r1
    inc  r1                     # r1 = -r1
    add  r2, r1                 # r1 = arr[2] - arr[1]
    bgt  r1, L2                 # if (arr[2] > arr[1]) goto L2
    ld   $0x0, r2               # r2 = 0
    br   L3                     # goto L3
L2:
    ld   $0x1, r2               # r2 = 1
L3:
    br   L7                     # goto L7
A5:
    not  r2                     # r2 = ~r2
    inc  r2                     # r2 = -r2
    add  r1, r2                 # r2 = arr[1] - arr[2]
    beq  r2, L4                 # if (arr[1] == arr[2]) goto L4
    ld   $0x0, r2               # r2 = 0
    br   L5                     # goto L5
L4:
    ld   $0x1, r2               # r2 = 1
L5:
    br   L7                     # goto L7
L6:
    ld   $0x0, r2               # r2 = 0
    br   L7                     # goto L7
L7:
    mov  r2, r0                 # r0 = r2
    j    0x0(r6)                # goto (r6)

.pos 0x400                      #
    .long 0x00000330            # A0 0
    .long 0x00000384            # L6 1
    .long 0x00000334            # A1 2 
    .long 0x00000384            # L6 3
    .long 0x0000033c            # A2 4
    .long 0x00000384            # L6 5 
    .long 0x00000354            # A4 6
    .long 0x00000384            # L6 7
    .long 0x0000036c            # A5 8
.pos 0x1000                     # stack
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000