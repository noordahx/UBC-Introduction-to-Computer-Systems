#include <stdlib.h>
#include <stdio.h>

// YOU: Allocate these global variables, using these names
int  p, m;
int* e;
int  z[10];

int main (int argv, char** argc) {
  // Ignore this block of code
  if (argv != 11) {
    fprintf (stderr, "usage: z[0] ... z[9]\n");
    exit (EXIT_FAILURE);
  }
  for (int c=0; c<10; c++)
    z[c] = atol (argc[1 + c]);

  // YOU: Implement this code
  p  = z[7];
  p  = z[p];
  e  = &m;
  *e = 1;
  e  = &z[z[6]];
  *e = *e + z[8];

  // Ignore this block of code
  printf ("p=%d m=%d e=&z[%d] z={", p, m, e - z);
  for (int c=0; c<10; c++)
    printf("%d%s", z[c], c<9? ", ": "}\n");
  }
