.pos 0x100
                ld $k, r0               # r0 = address of k
                ld $x, r1               # r1 = address of x
                ld $l, r2               # r2 = address of l
                ld $g, r3               # r3 = address of g
                ld (r1), r4             # r4 = x
                ld (r0, r4, 4), r5      # r5 = k[x]
                inca r4                 # r4 = x+4
                dec r4                  # r4 = x+3
                ld (r0, r4, 4), r6      # r6 = k[x+3]
                add r6, r5              # r5 = k[x] + k[x+3]
                st r5, (r3)             # g = k[x] + k[x+3]
                ld $0xf0, r6            # r6 = 0xf0
                and r6, r5              # r5 = r5 & 0xf0
                st r5, (r2)             # l = g & 0xf0
                halt                    # halt
.pos 0x1000
k:              .long 0x64              # k[0]
                .long 0xffffffff        # k[1]
                .long 0xffffffff        # k[2]
                .long 0xc8              # k[3]
                .long 0xffffffff        # k[4]
                .long 0xffffffff        # k[5]
                .long 0xffffffff        # k[6]
                .long 0xffffffff        # k[7]        
.pos 0x2000
x:              .long 0x0               # x
.pos 0x3000
l:              .long 0x0              # l
.pos 0x4000
g:              .long 0x0              # g