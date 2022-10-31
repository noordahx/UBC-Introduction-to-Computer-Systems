.pos 0x100
step_1:     br calculate_average
step_2:     br swap_ascending
step_3:     br find_median
finish:     halt




find_median:
            ld $s, r7
            ld (r7), r7
            ld $m, r6
            ld $n, r0
            ld (r0), r0
            
            shr $1, r0              # r0 = n/2

            mov r0, r1
            mov r0, r2
            shl $2, r1
            shl $1, r2
            add r2, r1              

            ld (r7,r1,4), r2        # r2 = median sid
            st r2, (r6)
            br finish               # yay!!!!!!!! the answer is 42

calculate_average:
            ld $n, r0               # r0 = &n
            ld (r0), r0             # r0 = n
            ld $s, r7               # r7 = &s
            ld (r7), r7             # r7 = s
            ld $0x0, r1             # r1 = x'
            br loop_average

loop_average:
            mov r1, r2              # r2 = x'
            not r2
            inc r2                  # r2 = -x'
            add r0, r2              # r2 = n-x'
            bgt r2, each_average
            br step_2

each_average:
            ld $0x0, r4
            mov r1, r2              # r2 = x'
            mov r1, r3              # r3 = x'
            shl $2, r2              # r2 = 4*x'
            shl $1, r3              # r3 = 2*x'
            add r3, r2              # r2 = 6*x'
            inc r2                  # r2 = 6*x'+1
            ld (r7,r2,4), r4        # r4 += g[0]
            inc r2
            ld (r7,r2,4), r3        # r4 += g[1]
            add r3, r4
            inc r2
            ld (r7,r2,4), r3        # r4 += g[2]
            add r3, r4
            inc r2
            ld (r7,r2,4), r3        # r4 += g[3]
            add r3, r4
            inc r2
            shr $2, r4
            st r4, (r7,r2,4)        # avg = r4
            inc r1
            br loop_average




swap_ascending:
            ld $s, r7                        
            ld (r7), r7             # r7 = s

            ld $n, r0
            ld (r0), r0             
            dec r0                  # r0 = n-1 = i'
            br outer_loop

outer_loop:
            ld $0x1, r1
            bgt r0, inner_loop
            br step_3

inner_loop:
            mov r1, r2
            not r2
            inc r2                  # r2 = -j'
            add r0, r2              # r2 = i-j
            inc r2
            bgt r2, if_cond
            dec r0
            br outer_loop

if_cond:    # j = r1
            mov r1, r2
            mov r1, r3
            shl $2, r2
            shl $1, r3
            add r3, r2              
            mov r2, r4              # r4 = 6*j'

            mov r1, r2
            mov r1, r3
            dec r2
            dec r3
            shl $2, r2
            shl $1, r3
            add r3, r2              
            mov r2, r5              # r5 = 6*(j'-1)

            inca r4
            inc r4
            inca r5
            inc r5


            ld (r7,r5,4), r2        # r2 = a[6*(j'-1)]
            ld (r7,r4,4), r3        # r3 = a[6*(j')]

            not r3
            inc r3
            add r3, r2              # r2 = a[j-1]-a[j]
            bgt r2, swap
            inc r1
            br inner_loop
            
swap:       # swap(a[j],a[j-1])    j = r1
            mov r1, r2
            mov r1, r3
            dec r2
            dec r3
            shl $2, r2
            shl $1, r3
            add r3, r2              
            mov r2, r4              # r4 = 6*(j'-1)

            mov r1, r2
            mov r1, r3
            shl $2, r2
            shl $1, r3
            add r3, r2              
            mov r2, r5              # r5 = 6*(j')

            mov r4, r2              # r2 = 6*(j'-1)
            mov r5, r3              # r3 = 6*(j')


            ld (r7,r2, 4), r4       # r4 = temp1
            ld (r7,r3, 4), r5       # r5 = temp2
            st r5, (r7,r2, 4)
            st r4, (r7,r3, 4)

            inc r2
            inc r3
            ld (r7,r2, 4), r4       # r4 = temp1
            ld (r7,r3, 4), r5       # r5 = temp2
            st r5, (r7,r2, 4)
            st r4, (r7,r3, 4)

            inc r2
            inc r3
            ld (r7,r2, 4), r4       # r4 = temp1
            ld (r7,r3, 4), r5       # r5 = temp2
            st r5, (r7,r2, 4)
            st r4, (r7,r3, 4)

            inc r2
            inc r3
            ld (r7,r2, 4), r4       # r4 = temp1
            ld (r7,r3, 4), r5       # r5 = temp2
            st r5, (r7,r2, 4)
            st r4, (r7,r3, 4)

            inc r2
            inc r3
            ld (r7,r2, 4), r4       # r4 = temp1
            ld (r7,r3, 4), r5       # r5 = temp2
            st r5, (r7,r2, 4)
            st r4, (r7,r3, 4)

            inc r2
            inc r3
            ld (r7,r2, 4), r4       # r4 = temp1
            ld (r7,r3, 4), r5       # r5 = temp2
            st r5, (r7,r2, 4)
            st r4, (r7,r3, 4)
            br inner_loop


.pos 0x3000
n:      .long 5       # just one student
m:      .long 0       # put the answer here
s:      .long base    # address of the array
base:   .long 1111    # student ID
        .long 80      # grade 0
        .long 60      # grade 1
        .long 78      # grade 2
        .long 90      # grade 3
        .long 0       # computed average    

        .long 2222    # student ID
        .long 10      # grade 0
        .long 20      # grade 1
        .long 30      # grade 2
        .long 40      # grade 3
        .long 0       # computed average   


        .long 3333    # student ID
        .long 50      # grade 0
        .long 60      # grade 1
        .long 70      # grade 2
        .long 80      # grade 3
        .long 0       # computed average  

        .long 4444    # student ID
        .long 1       # grade 0
        .long 2       # grade 1
        .long 3       # grade 2
        .long 4       # grade 3
        .long 0       # computed average   

        .long 5555    # student ID
        .long 5       # grade 0
        .long 10      # grade 1
        .long 15      # grade 2
        .long 20      # grade 3
        .long 0       # computed average   