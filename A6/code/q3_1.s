.pos 0x100
        ld $n, r7       # r7 = &n
        ld (r7), r7     # r7 = n

        ld $s, r6       # r6 = &s
        ld (r6),r6      # r6 = s

        ld $0x0, r5     # r5 = i'



loop_calc_average:
        mov r5, r4      # r4 = i'
        not r4
        inc r4          # r4 = -i'
        add r7,r4       # r4 = n-i'
        bgt r4, calculate_average
        br sort

sort:   
        mov r7, r5      # r5 = n
        dec r5          # r5 = n-1
        br sort_outer_loop


median:



sort_outer_loop:
        mov r5, r4      # r4 = i'
        ld $0x1, r3     # r3 = j' = 1
        bgt r4, sort_inner_loop
        br median

sort_inner_loop:
        mov r3, r2      # r2 = j'
        not r2
        inc r2          # r2 = -j'
        inc r2          # r2 = -j+1
        add r4, r2      # r2 = i'-j'+1
        bgt r2, sort_if
        dec r5
        br sort_outer_loop

sort_if:
        mov r3, r1      # r1 = r3 = j'
        mov r3, r2      # r2 = r3 = j'
        shl $2, r1      # r1 = 4*j'    
        shl $1, r2      # r2 = 2*j'
        add r2, r1      # r1 = 6*j'
        inca r1         # r1 = 6*j' + 4
        inc r1          # r1 = 6*j' + 5
        ld (r6, r1, 4), r2  # r2 = a[j]
        deca r1
        dec r1
        dec r1
        ld (r6, r1, 4), r0  # r1 = a[j-1]
        not r2
        inc r2
        add r2, r0      # r0 = a[j-1] - a[j]
        bgt r0, swap
        br sort_inner_loop
        inc r3

swap:
        mov r1, r2
        inca r1
        inc r1
        inc r1
        ld (r6,r2,4), r0
        ld (r6,r1,4), r1
        st 



median:
        halt


calculate_average:
        mov r5, r3      # r3 = i'  
        mov r5, r4      # r4 = i'
        shl $2, r3      # r3 = 4 * i'
        shl $1, r4      # r4 = 2 * i'

        add r4, r3      # r3 = 6 * i'
        inc r3          # r3 = 6 * i' + 1

        inc r5          # i'++
        ld $0x0, r4     # r4 = 0

        ld $0x0, r2     # r2 = j'

loop_avg:   
        mov r2, r1      # r1 = j'
        not r1          
        inc r1          # r1 = -j'
        inca r1         # r1 = 4 - j'
        bgt r1, avg
        shr $2, r4      # r4 = r4 / 4
        st r4, (r6, r3, 4)   # average = r4

        br loop_calc_average

avg:    
        ld (r6, r3, 4), r0  # r0 = grade[6 * i' + 1 + 1 * j']
        add r0, r4      # r4 += grade[24 * i' + 1 + 1 * j']

        inc r2          # j'++
        inc r3         # r3+=1
        br loop_avg




.pos 0x2000
n:      .long 2       # just one student
m:      .long 0       # put the answer here
s:      .long base    # address of the array
base:   .long 1234    # student ID
        .long 80      # grade 0
        .long 60      # grade 1
        .long 78      # grade 2
        .long 90      # grade 3
        .long 0       # computed average      
        
        
        
        
        .long 1234    # student ID
        .long 4      # grade 0
        .long 8      # grade 1
        .long 12      # grade 2
        .long 16      # grade 3
        .long 0       # computed average          
         