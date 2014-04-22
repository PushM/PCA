#include <stdio.h>
#include <stdlib.h>


#define MAX_POS (1<<22) 



void distribution_sort(int *S, int *D, int n, int bits)
{

   int max_value = (1<<bits)-1;
   int shift = (sizeof(int)<<3)-bits;
   static int index[MAX_POS]; 
   int i, j, tmp, tmpp;
   register int in;


   for (i=0;i<max_value;i++) 
      index[i] = 0;

   /* Histograma de valors pels bits log2(MAX_POS) més baixos */
   for(i = 0;i<n; i++) 
   {
     j = (S[i]>>shift) & max_value;
     index[j] = index[j]+1;
   }

   tmp = index[0];
   index[0] = 0;
   for (i=0; i<max_value; i++) 
   {
      tmpp = tmp + index[i];
      tmp  = index[i+1];
      index[i+1] = tmpp;
   }

   for(i = 0; i<n; i++) 
   {
      j = ((S[i]>>shift)&max_value);
      in = index[j];
      D[in] = S[i];
      index[j] = index[j]+1;
   }


}

#define N 1000000
#define BITS 4
typedef enum {RANDOM, GOINGUP} Tdistribution;
#define SYNTAX_EXECUTION "Usage: exec n dist_bits distribution (1=GOINGUP)\n" 

int main(int argc, char *argv[])
{

  int *D;
  int *S;
  int n, i;
  int bits;
  Tdistribution  dist;
  int tmp;


  if (argc == 4)
  {
      n =atoi(argv[1]);
      bits = atoi(argv[2]);
      tmp = atoi(argv[3]);
      if (tmp == 1) dist = GOINGUP;
      else dist=RANDOM;
  }
  else 
  {
      printf(SYNTAX_EXECUTION);
      exit(0);
  }

  D = (int *)malloc(sizeof(int)*n);
  S = (int *)malloc(sizeof(int)*n);

  if (dist==RANDOM)
  { 
    for (i=0; i<n; i++) 
    { 
     S[i] = random() & 0x7FFFFFFF;
    }
  }
  else
  {
    for (i=0; i<n; i++) 
    { 
     if (i&1)
         S[i] = i;
     else 
         S[i] = n-i;
    }
  }

  distribution_sort(S, D, n, bits);

  return 0;
}


