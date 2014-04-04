#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define OUTPUT_BUFFER_SIZE 100
#define INNER_BODY(_k,_quo)	u = r + x[_k];\
        					q = quores ## _quo[u][0];\
							r = quores ## _quo[u][1];\
				        	x[_k] = q;

#define INNER_LONG_BODY(k)	v = ((r << 3) + r + r) + x[k];\
							q = v / n;\
							r = v % n;\
							x[k] = q;

#define INNER_MULT_BODY(k)	q = n * x[k] + r;\
					        r = q / 10;\
					        x[k] = q - r*10;

#ifndef UNROLL_DEG
	#define	UNROLL_DEG	4
#endif

int N, N4;
char a[10240], b[10240], c[10240];
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
		INNER_BODY(k,5)
		INNER_BODY(k+1,5)
		INNER_BODY(k+2,5)
		INNER_BODY(k+3,5)
    }

	for(; k <= N4; k++) {
		INNER_BODY(k,5)
	}
}

void DIVIDE25(char *x)
{
    unsigned k, q, r, u;
	
	r = 0;                                       
	for(k = 0; k <= N4-(UNROLL_DEG-1); k+=UNROLL_DEG) {
		INNER_BODY(k,25)
		INNER_BODY(k+1,25)
		INNER_BODY(k+2,25)
		INNER_BODY(k+3,25)
    }
	for(; k <= N4; k++) {
		INNER_BODY(k,25)
	}
}

void DIVIDE239(char *x)                           
{
    unsigned k, q, r, u;

    r = 0;
    for(k = 0; k <= N4-(UNROLL_DEG-1); k+=UNROLL_DEG) {	
		INNER_BODY(k,239)
		INNER_BODY(k+1,239)
		INNER_BODY(k+2,239)
		INNER_BODY(k+3,239)
	}
	for(; k <= N4; k++) {
		INNER_BODY(k,239)
	}
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
		INNER_LONG_BODY(k)
		INNER_LONG_BODY(k+1)
		INNER_LONG_BODY(k+2)
		INNER_LONG_BODY(k+3)
	}
	for(; k <= N4; k++) {
		INNER_LONG_BODY(k)
	}
}

void MULTIPLY( char *x, int n )
{
    int j, k;
    unsigned q, r, u;
    long v;
    r = 0;
    for( k = N4; k >= UNROLL_DEG-1; k-=UNROLL_DEG )
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
    int j, k;
    unsigned q, r, u;
    long v;
    for( k = N4; k >= 0; k-- )                   
    {                    
//TODO unroll pendent		
        if( (x[k] = y[k] - z[k]) < 0 )           
        {                                        
            x[k] += 10;                          
            z[k-1]++;                            
        }
    }                                            
}


void calculate( void );
void progress( void );
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

    SET( a, 0 );
    SET( b, 0 );

    for( j = 2 * N4 + 1; j >= 3; j -= 2 )
    {
        SET( c, 1 );
        LONGDIV( c, j );

//GRUPO 1
        SUBTRACT( a, c, a );
        SUBTRACT( b, c, b );
//<\GRUPO 1>

//TEAM 2
		DIVIDE25( a );
        DIVIDE239( b );
        DIVIDE239( b );
//<\TEAM 2>
//BUFFERING PROGRESS
        progress();
    }

    SET( c, 1 );

    SUBTRACT( a, c, a );
	DIVIDE5( a );

    SUBTRACT( b, c, b );
    DIVIDE239( b );

    MULTIPLY( a, 4 );
    SUBTRACT( a, a, b );
    MULTIPLY( a, 4 );

    progress();
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

