#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int u[25][10];
    unsigned char q[250];
    unsigned char r[250][10];
} taules25;

typedef struct {
    unsigned int u[5][10];
    unsigned char q[50];
    unsigned char r[50][10];
} taules5;

typedef struct {
    unsigned int u[239][10];
    unsigned char q[2390];
    unsigned char r[2390][10];
} taules239;

int N, N4;
char a[10240], b[10240], c[10240];
char string[100];
taules25 t25;
taules5 t5;
taules239 t239;

void ompletaula25(){
    unsigned int i,j;
    for (i = 0; i < 250; i++) {
        t25.q[i] = i/25;
        for (j = 0; j < 10; j++) {
            t25.r[i][j] = i - j*25;
        }
    }
    //TO INTEGRATATION WITH ARRIBATION
    for (j = 0; j < 25; j++) {
        for (i = 0; i < 10; i++) {
            t25.u[j][i] = j*10 + i;
        }
    }
    // HASTA AQUIRL
}

void ompletaula5(){
    unsigned int i,j;
    for (i = 0; i < 50; i++) {
        t5.q[i] = i/5;
        for (j = 0; j < 10; j++) {
            t5.r[i][j] = i - j*5;
        }
    }
    //TO INTEGRATATION WITH ARRIBATION
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 10; i++) {
            t5.u[j][i] = j*10 + i;
        }
    }
    // HASTA AQUIRL
}

void ompletaula239(){
    unsigned long int i,j;
    for (i = 0; i < 2390; i++) {
        t239.q[i] = i/239;
        for (j = 0; j < 10; j++) {
            t239.r[i][j] = i - j*239;
        }
    }
    //TO INTEGRATATION WITH ARRIBATION
    for (j = 0; j < 239; j++) {
        for (i = 0; i < 10; i++) {
            t239.u[j][i] = j*10 + i;
        }
    }
    // HASTA AQUIRL
}

void inline DIVIDE25( char *x )                           
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;                                       
    for( k = 0; k <= N4; k++ )                  
    {                                            
        u = t25.u[r][x[k]];                       
        q = t25.q[u];                               
        r = t25.r[u][q];                          
        x[k] = q;                                
    }                                           
}

void inline DIVIDE5( char *x )                           
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;                                       
    for( k = 0; k <= N4; k++ )                  
    {                                            
        u = t5.u[r][x[k]];                       
        q = t5.q[u];                               
        r = t5.r[u][q];                          
        x[k] = q;                                
    }                                           
}

void inline DIVIDE239( char *x )                           
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;                                       
    for( k = 0; k <= N4; k++ )                  
    {                                            
        u = t239.u[r][x[k]];                       
        q = t239.q[u];                               
        r = t239.r[u][q];                          
        x[k] = q;                                 
    }                                           
}
//
//void inline DIVIDE( char *x, int n )                           
//{                                                
//    int j, k;
//    unsigned q, r, u;
//    long v;
//
//    r = 0;                                       
//    for( k = 0; k <= N4; k++ )                  
//    {                                            
//        u = r * 10 + x[k];                       
//        q = u / n;                               
//        r = u - q * n;                           
//        x[k] = q;                                
//    }                                           
//}

void inline LONGDIV( char *x, int n )                          
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    if( n < 6553 )                               
    {                                            
        r = 0;                                   
        for( k = 0; k <= N4; k++ )               
        {                                        
            u = r * 10 + x[k];                   
            q = u / n;                           
            r = u - q * n;                       
            x[k] = q;                            
        }                                       
    }                                            
    else                                         
    {                                            
        r = 0;                                   
        for( k = 0; k <= N4; k++ )              
        {                                       
            if( r < 6553 )                      
            {                                   
                u = r * 10 + x[k];              
                q = u / n;                      
                r = u - q * n;                  
            }                                   
            else                                
            {                                   
                v = (long) r * 10 + x[k];       
                q = v / n;                      
                r = v - q * n;                  
            }                                   
            x[k] = q;                           
        }                                       
    }                                           
}

void inline MULTIPLY( char *x, int n )                        
{                                            
    int j, k;
    unsigned q, r, u;
    long v;
    r = 0;                                   
    for( k = N4; k >= 0; k-- )               
    {                                        
        q = n * x[k] + r;                    
        r = q / 10;                          
        x[k] = q - r * 10;                   
    }                                        
}

void inline SET( char *x, int n )                              
{                                                
    memset( x, 0, N4 + 1 );                      
    x[0] = n;                                    
}


void inline SUBTRACT( char *x, char *y, char *z )                      
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

    setbuf(stdout, NULL);
    
//    ompletaula25();
    ompletaula5();
    ompletaula239();

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
//        DIVIDE25( a );
        DIVIDE5( a );
        DIVIDE5( a );

        SUBTRACT( b, c, b );
        DIVIDE239( b );
        DIVIDE239( b );

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
    int j;

    {
        fprintf( stdout, " \n3.");
        for( j = 1; j <= N; j++ )
        {
            fprintf( stdout, "%d", a[j]);
            if( j % 5  == 0 )
                if( j % 50 == 0 )
                    if( j % 250  == 0 )
                        fprintf( stdout, "    <%d>\n\n   ", j );
                    else
                        fprintf( stdout, "\n   " );
                else
                    fprintf( stdout, " " );
        }
    }
}

