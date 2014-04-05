#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define OUTPUT_BUFFER_SIZE 100

#define INNER_BODY(_k,_var,_res,_quo) 	u = r ## _res + _var[_k];\
										q = quores ## _quo[u][0];\
										r ## _res = quores ## _quo[u][1];\
										_var[_k] = q;

#define INNER_LONG_BODY(k,_dst,_org)	v = ((r << 3) + r + r) + _org[k];\
										q = v / n;\
										r = v % n;\
										_dst[k] = q;

#define INNER_MULT_BODY(k)	q = n * x[k] + r;\
					        r = q / 10;\
					        x[k] = q - r*10;
							
#define SUBTRACT_BODY(k) 	x[k] = y[k] - z[k];\
							aux = x[k] >> 31;\
							x[  k  ] += aux & 10;\
							z[k - 1] += aux & 1;

#define DUAL_SUBTRACT_BODY(k)	a[k] = c[k] - a[k];\
								aux = a[k] >> 31;\
								a[  k  ] += aux & 10;\
								a[k - 1] += aux & 1;\
								\
								b[k] = c[k] - b[k];\
								aux = b[k] >> 31;\
								b[  k  ] += aux & 10;\
								b[k - 1] += aux & 1;


#ifndef UNROLL_DEG
	#define	UNROLL_DEG	4
#endif

int N, N4;
char a[10240], b[10240], c[10240], ones[10240];
char string[OUTPUT_BUFFER_SIZE];

unsigned short quores239[2390][2];
unsigned char quores25[250][2];
unsigned char quores5[50][2];

void ompletaules(){
    unsigned i;
	
	// MEMOIZATION DIVIDE239
	for (i = 0; i < 2390; i++) {
		quores239[i][0] = i/239;
		quores239[i][1] = (i % 239) * 10;
	}
	
	// MEMOIZATION DIVIDE25
	for (i = 0; i < 250; i++) {
		quores25[i][0] = i/25;
		quores25[i][1] = (i % 25) * 10;
	}
	
	// MEMOIZATION DIVIDE5
	for (i = 0; i < 50; i++) {
		quores5[i][0] = i/5;
		quores5[i][1] = (i % 5) * 10;
	}
}

void DIVIDE5(char *x)
{
    unsigned k, q, r, u;
	
	r = 0;                                       
	for(k = 0; k <= N4-(UNROLL_DEG-1); k+=UNROLL_DEG) {
		INNER_BODY(k, x, , 5)
		INNER_BODY(k+1, x, , 5)
		INNER_BODY(k+2, x, , 5)
		INNER_BODY(k+3, x, , 5)
    }

	for(; k <= N4; k++) {
		INNER_BODY(k, x, , 5)
	}
}

void DIVIDE25(char *x)
{
    unsigned k, q, r, u;
	
	r = 0;                                       
	for(k = 0; k <= N4-(UNROLL_DEG-1); k+=UNROLL_DEG) {
		INNER_BODY(k, x, , 25)
		INNER_BODY(k+1, x, , 25)
		INNER_BODY(k+2, x, , 25)
		INNER_BODY(k+3, x, , 25)
    }
	for(; k <= N4; k++) {
		INNER_BODY(k, x, , 25)
	}
}

void DIVIDE239(char *x)                           
{
    unsigned k, q, r, u;

    r = 0;
    for(k = 0; k <= N4-(UNROLL_DEG-1); k+=UNROLL_DEG) {
		INNER_BODY(k, x, , 239)
		INNER_BODY(k+1, x, , 239)
		INNER_BODY(k+2, x, , 239)
		INNER_BODY(k+3, x, , 239)
	}
	for(; k <= N4; k++) {
		INNER_BODY(k, x, , 239)
	}
}

void MASOCHISTIC_DIVIDE( char *a, char *b, char *c, char *ones, int n )
{
	unsigned k, q, u, v, r, r25, r239_1, r239_2;

	r = r25 = r239_1 = r239_2 = 0;
	
	INNER_BODY(0, a, 25, 25)
	INNER_BODY(0, b, 239_1, 239)
	INNER_LONG_BODY(0, c, ones)
	for(k = 1; k <= N4-(UNROLL_DEG-1) - 1; k += UNROLL_DEG) {
		INNER_BODY(  k  , a, 25, 25)
		INNER_BODY(  k  , b, 239_1, 239)
		INNER_BODY(k - 1, b, 239_2, 239)
		INNER_LONG_BODY(k, c, ones)
		
		INNER_BODY(k + 1, a, 25, 25)
		INNER_BODY(k + 1, b, 239_1, 239)
		INNER_BODY(  k  , b, 239_2, 239)
		INNER_LONG_BODY(k + 1, c, ones)
		
		INNER_BODY(k + 2, a, 25, 25)
		INNER_BODY(k + 2, b, 239_1, 239)
		INNER_BODY(k + 1, b, 239_2, 239)
		INNER_LONG_BODY(k + 2, c, ones)
		
		INNER_BODY(k + 3, a, 25, 25)
		INNER_BODY(k + 3, b, 239_1, 239)
		INNER_BODY(k + 2, b, 239_2, 239)
		INNER_LONG_BODY(k + 3, c, ones)
	}
	for(; k <= N4; k++) {
		INNER_BODY(  k  , a, 25, 25)
		INNER_BODY(  k  , b, 239_1, 239)
		INNER_BODY(k - 1, b, 239_2, 239)
		INNER_LONG_BODY(k, c, ones)
	}
	INNER_BODY(k - 1, b, 239_2, 239)
}

void DIVIDE( char *x, int n )                           
{
    unsigned k, q, r, u;

    r = 0;
    for( k = 0; k <= N4; k++ )
    {
        u = r*10 + x[k];
        q = u / n;
		r = u % n;
        x[k] = q;
    }
}

void LONGDIV( char *x, int n )                          
{
    unsigned k, q, r, u, v;
	
	// proc de 64bits
	r = 0;
	for( k = 0; k <= N4 - (UNROLL_DEG - 1); k += UNROLL_DEG ) {
		INNER_LONG_BODY( k , x, x)
		INNER_LONG_BODY(k+1, x, x)
		INNER_LONG_BODY(k+2, x, x)
		INNER_LONG_BODY(k+3, x, x)
	}
	for(; k <= N4; k++) {
		INNER_LONG_BODY(k, x, x)
	}
}

void LONGDIV2( char *x, char *y, int n )                          
{
    unsigned k, q, r, u, v;
	
	// proc de 64bits
	r = 0;
	for( k = 0; k <= N4 - (UNROLL_DEG - 1); k += UNROLL_DEG ) {
		INNER_LONG_BODY(  k  , x, y)
		INNER_LONG_BODY(k + 1, x, y)
		INNER_LONG_BODY(k + 2, x, y)
		INNER_LONG_BODY(k + 3, x, y)
	}
	for(; k <= N4; k++) {
		INNER_LONG_BODY(k, x, y)
	}
}

void MULTIPLY( char *x, int n )
{
    int k;
    unsigned q, r, u;
    r = 0;
    for( k = N4; k >= UNROLL_DEG-1; k -= UNROLL_DEG )
    {
		INNER_MULT_BODY(k)
		INNER_MULT_BODY(k-1)
		INNER_MULT_BODY(k-2)
		INNER_MULT_BODY(k-3)
    }
	for(; k >= 0; k--) {
		INNER_MULT_BODY(k)
	}
}

void SET( char *x, int n )                              
{                                                
    memset( x, 0, N4 + 1 );                      
    x[0] = n;                                    
}


void SUBTRACT( char *x, char *y, char *z )                      
{                                                
    int k, aux;
    for( k = N4; k >= UNROLL_DEG - 1; k -= UNROLL_DEG ) {
		SUBTRACT_BODY(k)
		SUBTRACT_BODY(k - 1)
		SUBTRACT_BODY(k - 2)
		SUBTRACT_BODY(k - 3)
    }
    for(; k >= 0; k--) {
		SUBTRACT_BODY(k);
	}
}

void DUAL_SUBTRACT( char *a, char *b, char *c )
{
	// a = c - a
	// b = c - b
	
	int k, aux;
	for( k = N4; k >= UNROLL_DEG - 1; k -= UNROLL_DEG ) {
		DUAL_SUBTRACT_BODY(k)
		DUAL_SUBTRACT_BODY(k - 1)
		DUAL_SUBTRACT_BODY(k - 2)
		DUAL_SUBTRACT_BODY(k - 3)
	}
	for(; k >= 0; k--) {
		DUAL_SUBTRACT_BODY(k)
	}
}


void calculate( void );
void progress( void );
void progressBuff( void );
void epilog( void );


int main( int argc, char *argv[] )
{
    N = 10000;
	if (argc > 1)
		N = atoi(argv[1]);
	
    setbuf(stdout, NULL);
    
    ompletaules();

    calculate();

    epilog();

    return 0;
}

void calculate( void )
{
    int j;

    N4 = N + 4;
	j = 2 * N4 + 1;

    SET( a, 0 );
    SET( b, 0 );
	
	SET( ones, 1 );
	LONGDIV2(c, ones, j);	// c = ones / j

    for(; j >= 3; j -= 2 )
    {
		// LOOP FUSION GROUP 1
		DUAL_SUBTRACT( a, b, c );	// SUBTRACT( a, c, a )
									// SUBTRACT( b, c, b )

		// LOOP FUSION GROUP 2
		MASOCHISTIC_DIVIDE( a, b, c, ones, j - 2);	// DIVIDE25( a )
													// DIVIDE239( b )
													// DIVIDE239( b )
													// SET( c, 1 ); -> s'ha substituit per un array estatic (ones)
													// LONGDIV( c, j - 2 ); -> per la seguent iteracio

		// TODO BUFFERING PROGRESS
        progress();
    }

    SUBTRACT( a, ones, a );
	DIVIDE5( a );

	SUBTRACT( b, ones, b );
    DIVIDE239( b );

	// TODO LOOP FUSION GROUP 3
    MULTIPLY( a, 4 );
    SUBTRACT( a, a, b );
    MULTIPLY( a, 4 );

	// TODO BUFFERING PROGRESS
    progress();
	//progressBuff();
}

/*

 N = 10000                      
 A = 0                          
 B = 0                          
 J = 2 * (N + 4) + 1            
 FOR J = J TO 3 STEP -2         
     A = (1 / J - A) / 5 ^ 2    
     B = (1 / J - B) / 239 ^ 2  
 NEXT J                         
 A = (1 - A) / 5                
 B = (1 - B) / 239              
 PI = (A * 4 - B) * 4           

*/

void progress( void )
{
    printf(".");
}

void progressBuff( void)
{
	unsigned mask = (unsigned)('.');
	mask |= (mask << 8);
	mask |= (mask << 16);
	mask |= (mask << 32);
	
	unsigned *buff = (unsigned *) malloc(sizeof(unsigned) * 500);
}

void epilog( void )
{
    unsigned j, buffer_i, aux;

    {
        fprintf( stdout, " \n3.");
        for( j = 1; j <= N;)
        {
			buffer_i = 0;
			while (buffer_i < (OUTPUT_BUFFER_SIZE - 20) && j <= N) {
				aux = 0;
				sprintf(&(string[buffer_i]), "%d", a[j]);
				if( j % 5  == 0 ) {
					if( j % 50 == 0 )
						if( j % 250  == 0 )
							aux = sprintf(&(string[buffer_i + 1]), "    <%d>\n\n   ", j);
						else
							aux = sprintf(&(string[buffer_i + 1]), "\n   ");
					else
						aux = sprintf(&(string[buffer_i + 1]), " ");
				}
				buffer_i += aux + 1;
				
				j++;
			}
			
			string[buffer_i] = '\0';
			fprintf(stdout, "%s", &(string[0]));
        }
    }
}

