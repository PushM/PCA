#include <stdio.h>
#include <stdlib.h>

#define N 1000

int n;

int C[N][N];
int A[N][N];
int B[N][N];


void mult1 ()
{

  int i,j,k;
  int sum;

  for ( i=0 ; i < n; i++ )
  {
    for ( j=0 ; j < n; j++ )
    {
      for ( k=0 ; k < n ; k++ )
         C[i][j]+= A[i][k]*B[k][j];
    }
  }
}

void mult2 ()
{

  int i,j,k;
  int r;

  for ( k=0 ; k < n; k++ )
  {
    for ( i=0 ; i < n; i++ )
    {
      r = A[i][k];
      for ( j=0 ; j < n ; j++ )
         C[i][j] += r*B[k][j];
    }
  }
}

void mult3 ()
{
  int i,j,k,r;

  for ( k=0 ; k < n; k++ )
  {
    for ( j=0 ; j < n; j++ )
    {
      r = B[k][j];
      for ( i=0 ; i < n ; i++ )
         C[i][j] += A[i][k]*r;
    }
  }
}

void init(int A[][N], int n)
{

  int i,j;

  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      A[i][j] = i+j;

}

int main(int argc, char *argv[])
{


  if (argc > 1) n = atoi(argv[1]); else n = N;

  init( A, n);
  init( B, n);
  init( C, n);
  

  mult1(C,B,A,n); 
  mult2(C,B,A,n); 
  mult3(C,B,A,n); 

  write(1, C, sizeof(C));
  return 0;
}
