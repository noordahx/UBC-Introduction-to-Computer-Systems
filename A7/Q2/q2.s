.pos 0x100
start:
    ld   $sb, r5         # r5 = &sb = address of last element of stack
    inca r5              # r5 += 4 = address of the element after stack
    gpc  $6, r6          # r6 = pc + 6 = return address
    j    main            # jump to main function
    halt

f:
    deca r5              # allocate 4 bytes in the stack
    ld   $0, r0          # r0 = 0
    ld   4(r5), r1       # r1 = 4(r5) = load second from top element of the stack
    ld   $0x80000000, r2 # r2 = 0x80000000
f_loop:
    beq  r1, f_end       # if (r1 == 0) GOTO f_end
    mov  r1, r3          # r3 = r1
    and  r2, r3          # r3 = r2 & r3
    beq  r3, f_if1       # if (r3 == 0) GOTO f_if1 *check if number if positive
    inc  r0              # r0++ = add 1 to return value if number is negative
f_if1:
    shl  $1, r1          # r1 = r1 * 2
    br   f_loop          # GOTO f_loop
f_end:
    inca r5              # deallocate 4 bytes in stack
    j    (r6)            # jump to called function (main)

main:
    deca r5              # allocate 4 bytes in stack
    deca r5              # allocate 4 butes in stack
    st   r6, 4(r5)       # store RA as the second element of the stack
    ld   $8, r4          # r4 = 8
main_loop:
    beq  r4, main_end    # if (r4 == 0) GOTO main_end
    dec  r4              # r4 -= 1
    ld   $x, r0          # r0 = &x
    ld   (r0, r4, 4), r0 # r0 = x[r4]
    deca r5              # allocate 4 bytes in the stack
    st   r0, (r5)        # store x[r4] in newly allocated space
    gpc  $6, r6          # r6 = pc + 6 = RA
    j    f               # jump to f
    inca r5              # deallocate 4 bytes
    ld   $y, r1          # r1 = &y
    st   r0, (r1, r4, 4) # y[r4] = r0 = return value of f function is stored in y[r4]
    br   main_loop       # GOTO main_loop
main_end:
    ld   4(r5), r6       # r6 = RA 
    inca r5              # deallocate 4 bytes in the stack
    inca r5              # deallocate 4 bytes in the stack
    j    (r6)            # jump to caller function (start)

.pos 0x2000
x:
    .long 1
    .long 2
    .long 3
    .long -1
    .long -2
    .long 0
    .long 184
    .long 340057058

y:
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0

.pos 0x8000
# These are here so you can see (some of) the stack contents.
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
sb: .long 0