.pos 0x100
                ld $array, r0           # r0 = address of array
                ld 0x4(r0), r1          # r1 = array[1]
                ld 0xc(r0), r3          # r3 = array[3]
                st r3, 0x4(r0)          # array[1] = r3
                st r1, 0xc(r0)          # array[3] = r1
                halt                    # halt
.pos 0x1000
array:          .long 0xffffffff        # array[0]
                .long 0x69        # array[1]
                .long 0xffffffff        # array[2]
                .long 0x42        # array[3]
                .long 0xffffffff        # array[4]
                .long 0xffffffff        # array[5]
