# CS213 Lecture 5
RTL:
```
a[2] = a[i];
```
Assembly:
```
ld $a, r0
ld $i, r1
ld (r1), r1
ld (r0, r1, 4), r2
st r2, 8(r0)
```
