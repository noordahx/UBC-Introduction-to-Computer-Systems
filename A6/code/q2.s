.pos 0x100
                ld $0x0, r0              # r0 = 0

                ld $n, r4               # r4 = &n
                ld (r4), r4             # r4 = n                
                
                ld $c, r5               # r5 = &c
                ld (r5), r5             # r5 = c

                ld $a, r6               # r6 = &a
                ld $b, r7               # r7 = &b      

loop:           mov r0, r1              # r1 = i
                not r1                  
                inc r1                  # r1 =-i
                add r4, r1              # r1 = n-i
                bgt r1, loop_body       # if (r1 > 0) GOTO loop_body
                br loop_exit            # else GOTO loop_exit

loop_body:      ld (r6, r0, 4), r2      # r2 = a[i]
                ld (r7, r0, 4), r3      # r3 = b[i]
                not r3
                inc r3                  # r3 = -b[i]
                add r3, r2              # r2 = a[i]-b[i]
                bgt r2, add_one         # if (r2 > 0) GOTO add_one
                br else                 # else GOTO else

add_one:        inc r5                  # c++
                br else                 # GOTO else


else:           inc r0                  # r0++
                br loop

loop_exit:      ld $i, r1               # r1 = &i
                st r0, (r1)             # a = r0
                ld $c, r1               # r1 = &c
                st r5, (r1)             # c = r5

                halt


.pos 0x2000
i:              .long 0xfffffffe        # i
n:              .long 0x5               # n
c:              .long 0x0               # c            
a:              .long 0x00000010        # a[0]
                .long 0x00000020        # a[1]
                .long 0x00000030        # a[2]
                .long 0x00000040        # a[3]
                .long 0x00000050        # a[4]
b:              .long 0x00000011        # b[0]
                .long 0x00000020        # b[1]
                .long 0x00000028        # b[2]
                .long 0x00000044        # b[3]
                .long 0x00000048        # b[4]
