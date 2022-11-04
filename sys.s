.pos 0x1000
ld $1,   r0
ld $str, r1
ld $12,  r2
sys  $1
halt
.pos 0x2000
str: .long 0x68656c6c # hell
.long 0x6f20776f # o wo
.long 0x726c640a # rld\n