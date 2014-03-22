#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define OUTPUT_BUFFER_SIZE 100

int N, N4;
char a[10240], b[10240], c[10240];
char string[OUTPUT_BUFFER_SIZE];

unsigned short quores239[2390][2];
//unsigned short res239[2390];

unsigned char quores25[250][2];
//unsigned char res25[250];

void ompletaules(){
    unsigned i;
	
	// MEMOIZATION DIVIDE239
	for (i = 0; i < 2390; i++) {
		/*quo239[i] = i/239;
		res239[i] = (i % 239) * 10;*/
		quores239[i][0] = i/239;
		quores239[i][1] = (i % 239) * 10;
	}
	
	// MEMOIZATION DIVIDE25
	for (i = 0; i < 250; i++) {
		/*quo25[i] = i/25;
		res25[i] = (i % 25) * 10;*/
		quores25[i][0] = i/25;
		quores25[i][1] = (i % 25) * 10;
	}
}

void DIVIDE25(char *x)
{
    unsigned k, q, r, u;
	
	r = 0;                                       
	for(k = 0; k <= N4; k++) {
		u = r + x[k];		// r*10 + x[k]
		q = quores25[u][0];	// u/25
		r = quores25[u][1];	// (u % 25) * 10
		x[k] = q;
    }
}

void DIVIDE239(char *x)                           
{
    unsigned k, q, r, u;

    r = 0;
    for(k = 0; k <= N4; k++) {
		u = r + x[k];			// r*10 + x[k]
		q = quores239[u][0];	// u/239
		r = quores239[u][1];	// (u % 239) * 10
		x[k] = q;
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
    unsigned k, q, r, u;
    unsigned long v;
	
	// proc de 64bits
	r = 0;
	for( k = 0; k <= N4; k++ )
	{
		v = (unsigned long) ((r << 3) + r + r) + x[k];
		q = v / n;
		r = v % n;
		x[k] = q;
	}
}

void MULTIPLY( char *x, int n )
{
    int j, k;
    unsigned q, r, u;
    long v;
    r = 0;
    for( k = N4; k >= 0; k-- )
    {
        q = n * x[k] + r;
        r = q / 10;
        x[k] = q - r*10;
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

        SUBTRACT( a, c, a );
		DIVIDE25( a );
        SUBTRACT( b, c, b );
        DIVIDE239( b );
        DIVIDE239( b );

        progress();
    }

    SET( c, 1 );

    SUBTRACT( a, c, a );
    DIVIDE( a, 5 );

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
        for( j = 1; j <= N; j++ )
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
			j--;
			
			/*fprintf( stdout, "%d", a[j]);
				if( j % 5  == 0 )
					if( j % 50 == 0 )
						if( j % 250  == 0 )
							fprintf( stdout, "    <%d>\n\n   ", j );
						else
							fprintf( stdout, "\n   " );
					else
						fprintf( stdout, " " );*/
        }
    }
}

