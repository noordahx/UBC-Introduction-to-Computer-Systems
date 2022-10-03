#include <stdio.h>
int k[8];
int x, l, g;

int main() {
	x = 0;
	k[0] = 100;
	k[3] = 200;
	g = k[x] + k[x+3];
	l = g & 0xf0;
	printf("%d\n%d\n", g,l);
	return 0;
}
