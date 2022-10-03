.pos 0x100
                ld $p, r6               # r7 = address of p
                ld $e, r7               # r8 = address of e
                ld (r7), r1             # r1 = e
                inc r1                  # e+1
                inca r1                 # e+4
                shl $0x4, r1            # e << 4
                ld (r7), r0             # r0 = e
                and r0, r1
                shr $0x2, r1
                st r1, (r6)
                halt                    # halt
.pos 0x1000
p:              .long 0xffffffff        # p
.pos 0x2000
e:              .long 0xff        # e