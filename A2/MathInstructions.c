#include <stdio.h>
int p,e = 10;
int main(){
	p = ((((e + 1) + 4) << 4) & e) / 4; 
	printf("%d", p);
}

