    gpc $16, r0
    ld $7, r1
    ld $64, r2
    sys $2
    halt
    .long 0x2f62696e
    .long 0x2f736800