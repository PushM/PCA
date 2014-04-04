#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N_ITER 10000000
#define INNER_ITER(_i,_j,_k) C[_i][_j] = C[_i][_j] + A[_i][_k] * B[_k][_j];

#define UNROLL_INNER_ITER(_i,_j) {\
	INNER_ITER(_i,_j,0)\
	INNER_ITER(_i,_j,1)\
	INNER_ITER(_i,_j,2)\
	INNER_ITER(_i,_j,3)\
}

#define UNROLL_SEMI_ITER(_i) {\
	UNROLL_INNER_ITER(_i,0)\
	UNROLL_INNER_ITER(_i,1)\
	UNROLL_INNER_ITER(_i,2)\
	UNROLL_INNER_ITER(_i,3)\
}
#define UNROLL_OUTER_ITER {\
	UNROLL_SEMI_ITER(0)\
	UNROLL_SEMI_ITER(1)\
	UNROLL_SEMI_ITER(2)\
	UNROLL_SEMI_ITER(3)\
}


void multiplica (int A[4][4], int B[4][4], int C[4][4], unsigned int n_iter)
{
  int iter;
  int i, j, k;

  for (iter = 0; iter < n_iter; iter++){
	  UNROLL_OUTER_ITER
  }
}

void
print_matriu (int C[][4])
{
  int i, j, k;

  for (i = 0; i < 4; i++)
    {
      for (j = 0; j < 4; j++)
	{
	  printf ("%d ", C[i][j]);
	}
      printf ("\n");
    }
}

int
main (int argc, char *argv[])
{
  int A[4][4], B[4][4], C[4][4] =
    { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
  unsigned int n_iter = N_ITER, i, j, k, iter;

  for (i = 0; i < 4; i++)
    {
      for (j = 0; j < 4; j++)
	{
	  A[i][j] = rand ();
	  B[i][j] = rand ();
	}
    }

  if (argc > 1)
    {
      n_iter = atoi (argv[1]);
    }
	multiplica(A,B,C,n_iter);
  print_matriu (C);

  return 0;
}
