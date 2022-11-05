.pos 0x0
    ld   $sb, r5         # r5 = &sp = address of last element in the stack
    inca r5              # r5 = &sp + 5 = address of element after stack
    gpc  $6, r6          # r6 = pc + 6
    j    0x300           # call function at 0x300
    halt                 # halt the program

.pos 0x100
    .long 0x00001000     # memory at address 0x100 stores 1000 as a value (m[0x100] = 1000)

.pos 0x200
    ld   (r5), r0        # r0 = (r5) = load first element of r5 to r0
    ld   4(r5), r1       # r1 = 4(r5) = load second element of r5 to r1
    ld   $0x100, r2      # r2 = 0x100
    ld   (r2), r2        # r2 = m[r2] = load the value stored at memory address 0x100 to r2
    ld   (r2, r1, 4), r3 # r3 = m[m[r2]+r1] = r2 turns out to point to an array, r3 will store r1'th elementh of that array
    add  r3, r0          # r0 = r0 + r3 = add array element to r0
    st   r0, (r2, r1, 4) # m[m[r2]+r1] = m[m[r2]+r1] + r0 = store r0 + array element at r1'th element of an array
    j    (r6)            # jump back to function 0c300

.pos 0x300
    ld   $-12, r0        # r0 = -12
    add  r0, r5          # r5 = r5 - 12 = allocate 12 bytes as func 0x300's frame
    st   r6, 8(r5)       # 0x300 frame's third element stores RA
    ld   $1, r0          # r0 = 1
    st   r0, (r5)        # 0x300 frame's first element stores 1
    ld   $2, r0          # r0 = 2
    st   r0, 4(r5)       # 0x3000 frame's second element stores 2
    ld   $-8, r0         # r0 = -8
    add  r0, r5          # function at 0x300 gets additional 8 bytes frame in the stack
    ld   $3, r0          # r0 = 3
    st   r0, (r5)        # additional frame's first element is 3
    ld   $4, r0          # r0 = 4
    st   r0, 4(r5)       # additional frame's second element is 4
    gpc  $6, r6          # r6 = pc + 6
    j    0x200           # call function at 0x200
    ld   $8, r0          # r0 = 8
    add  r0, r5          # deallocate additional stack place allocated earlier
    ld   (r5), r1        # r1 = function 0x300's main stack's first element
    ld   4(r5), r2       # r2 = function 0x300's main stack's second element
    ld   $-8, r0         # r0 = -8
    add  r0, r5          # allocate 8 bytes on top of function 0x300's main stack
    st   r1, (r5)        # newly allocated space's first element store r1
    st   r2, 4(r5)       # newly allocated space's second element store r2
    gpc  $6, r6          # r6 = pc + 6
    j    0x200           # call function at 0x200
    ld   $8, r0          # r0 = 8
    add  r0, r5          # deallocate addtional 8 bytes allocated on top of the stack
    ld   8(r5), r6       # r6 = RA = r6 lead return address to the function at 0x0
    ld   $12, r0         # r0 = 12
    add  r0, r5          # deallocate function 0x300's stack space
    j    (r6)            # jump back to function 0x0, then halt

.pos 0x1000              # array
    .long 0              # array[0]
    .long 0              # array[1]
    .long 0              # array[2]
    .long 0              # array[3]
    .long 0              # array[4]
    .long 0              # array[5]
    .long 0              # array[6]
    .long 0              # array[7]
    .long 0              # array[8]
    .long 0              # array[9]

.pos 0x8000
    # These are here so you can see (some of) the stack contents
    # while running the code on the simulator.
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
sb: .long 0              # stack bottom 
