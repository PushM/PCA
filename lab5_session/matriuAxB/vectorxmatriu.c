#include <stdio.h>
#include <stdlib.h>

#define N (1<<16)
#define M 1024 
#define BLOCK_SIZE 256 

typedef int Tele; 

void vectorPerMatriu(Tele vector[M], Tele matriu[][M], Tele dest[N])
{
  int i, j;

  for (i=0; i<N; i++)
     dest[i] = 0;
  
  for (i=0; i<N; i++)
  {
     for (j=0; j<M; j++)
     {
        dest[i]+=vector[j]*matriu[i][j];
     }
  }


}

void vectorPerMatriuBLOCKING ( Tele vector[M], int matriu[][M], Tele dest[N]) 
{
  int i, j;
  int i_limInf, i_limSup;
  int j_limInf, j_limSup;
  int sum;

  for (i=0; i<N; i++)
     dest[i] = 0;

  for ( i_limInf=0 ; i_limInf < N; i_limInf+=BLOCK_SIZE )
  {
     i_limSup = i_limInf + BLOCK_SIZE;

     for ( j_limInf=0 ; j_limInf < M; j_limInf+=BLOCK_SIZE )
     {
        j_limSup = j_limInf + BLOCK_SIZE;

        for ( j = j_limInf; j<j_limSup; j++)
        {
           for ( i = i_limInf; i < i_limSup; i++ )
              dest[i] += vector[j] * matriu[i][j];
        }
     }
  }
}


void vectorPerMatriuBLOCKINGvector ( Tele vector[M], int matriu[][M], Tele dest[N])
{

  int i, j;
  int i_limInf, i_limSup;
  int j_limInf, j_limSup;
  int sum;

  for (i=0; i<N; i++)
     dest[i] = 0;


  for ( j_limInf=0 ; j_limInf < M; j_limInf+=BLOCK_SIZE )
  {
      for ( i = 0; i<N ; i++ )
      {
        j_limSup = j_limInf + BLOCK_SIZE;
        for ( j = j_limInf; j<j_limSup; j++)
        {
            dest[i] += vector[j] * matriu[i][j];
        }
      }
   }  

}


