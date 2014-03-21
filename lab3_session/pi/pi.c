#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int N, N4;
char a[10240], b[10240], c[10240];
char string[100];
unsigned divisio239[2390];
unsigned multi239[10];
unsigned div5[50];

void ompletaules(){
    unsigned i;
    for (i = 0; i < 2390; i++) {
        divisio239[i] = i/239;
    }
    for (i = 0; i < 50; i++) {
        div5[i] = i/5;
    }
    multi239[0] = 0;
    multi239[1] = 239;
    multi239[2] = 239*2;
    multi239[3] = 239*3;
    multi239[4] = 239*4;
    multi239[5] = 239*5;
    multi239[6] = 239*6;
    multi239[7] = 239*7;
    multi239[8] = 239*8;
    multi239[9] = 239*9;
}



void DIVIDE5( char *x)                           
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;                                       
    for( k = 0; k <= N4; k+=4 )                  
    {                                            
        u = ((r << 3) + r + r) + x[k];                       
        q=div5[u];
        r = u - ((q << 2) + q);      
        x[k] = q;
        
        u = ((r << 3) + r + r) + x[k+1];                       
        q=div5[u];
        r = u - ((q << 2) + q);      
        x[k+1] = q; 
        
        u = ((r << 3) + r + r) + x[k+2];                       
        q=div5[u];
        r = u - ((q << 2) + q);      
        x[k+2] = q; 
        
        u = ((r << 3) + r + r) + x[k+3];                       
        q=div5[u];
        r = u - ((q << 2) + q);      
        x[k+3] = q; 
    }                                           
}

void DIVIDE239( char *x)                           
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;                                       
    for( k = 0; k <= N4; k+=4 )                  
    {                                            
        u = ((r << 3) + r + r) + x[k];                       
        q = divisio239[u];                               
        r = u - multi239[q];                           
        x[k] = q;
        
        u = ((r << 3) + r + r) + x[k+1];                       
        q = divisio239[u];                               
        r = u - multi239[q];                           
        x[k+1] = q;  
        
        u = ((r << 3) + r + r) + x[k+2];                       
        q = divisio239[u];                               
        r = u - multi239[q];                           
        x[k+2] = q;  
        
        u = ((r << 3) + r + r) + x[k+3];                       
        q = divisio239[u];                               
        r = u - multi239[q];                           
        x[k+3] = q;  
    }                                           
}

void DIVIDE( char *x, int n )                           
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;                                       
    for( k = 0; k <= N4; k++ )                  
    {                                            
        u = r*10 + x[k];                       
        q = u / n;                               
        r = u - q * n;                           
        x[k] = q;                                
    }                                           
}

void LONGDIV( char *x, int n )                          
{                                                
    int j, k;
    unsigned q, r, u;
    unsigned long v;

    if( n < 6553 )                               
    {                                            
        r = 0;                                   
        for( k = 0; k <= N4; k+=4 )               
        {                                        
            u = ((r << 3) + r + r) + x[k];                   
            q = u / n;                           
            r = u - q * n;                       
            x[k] = q; 
            
            u = ((r << 3) + r + r) + x[k+1];                   
            q = u / n;                           
            r = u - q * n;                       
            x[k+1] = q;
            
            u = ((r << 3) + r + r) + x[k+2];                   
            q = u / n;                           
            r = u - q * n;                       
            x[k+2] = q;
            
            u = ((r << 3) + r + r) + x[k+3];                   
            q = u / n;                           
            r = u - q * n;                       
            x[k+3] = q;
        }                                       
    }                                            
    else                                         
    {                                            
        r = 0;                                   
        for( k = 0; k <= N4; k+=4 )              
        {                                       
            if( r < 6553 )                      
            {                                   
                u = ((r << 3) + r + r) + x[k];              
                q = u / n;                      
                r = u - q * n;                  
            }                                   
            else                                
            {                                   
                v = (unsigned long) ((r << 3) + r + r) + x[k];       
                q = v / n;                      
                r = v - q * n;                  
            }                                   
            x[k] = q; 
            
            if( r < 6553 )                      
            {                                   
                u = ((r << 3) + r + r) + x[k+1];              
                q = u / n;                      
                r = u - q * n;                  
            }                                   
            else                                
            {                                   
                v = (unsigned long) ((r << 3) + r + r) + x[k+1];       
                q = v / n;                      
                r = v - q * n;                  
            }                                   
            x[k+1] = q;
            
            if( r < 6553 )                      
            {                                   
                u = ((r << 3) + r + r) + x[k+2];              
                q = u / n;                      
                r = u - q * n;                  
            }                                   
            else                                
            {                                   
                v = (unsigned long) ((r << 3) + r + r) + x[k+2];       
                q = v / n;                      
                r = v - q * n;                  
            }                                   
            x[k+2] = q;
            
            if( r < 6553 )                      
            {                                   
                u = ((r << 3) + r + r) + x[k+3];              
                q = u / n;                      
                r = u - q * n;                  
            }                                   
            else                                
            {                                   
                v = (unsigned long) ((r << 3) + r + r) + x[k+3];       
                q = v / n;                      
                r = v - q * n;                  
            }                                   
            x[k+3] = q;
        }                                       
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
        x[k] = q - ((r << 3) + r + r);                   
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
    for( k = N4; k >= 0; k-=4 )                   
    {                                            
        if( (x[k] = y[k] - z[k]) < 0 )           
        {                                        
            x[k] += 10;                          
            z[k-1]++;                            
        }
        
        if( (x[k-1] = y[k-1] - z[k-1]) < 0 )           
        {                                        
            x[k-1] += 10;                          
            z[k-2]++;                            
        } 
        
        if( (x[k-2] = y[k-2] - z[k-2]) < 0 )           
        {                                        
            x[k-2] += 10;                          
            z[k-3]++;                            
        } 
        
        if( (x[k-3] = y[k-3] - z[k-3]) < 0 )           
        {                                        
            x[k-3] += 10;                          
            z[k-4]++;                            
        } 
    }                                            
}


void calculate( void );
void progress( void );
void epilog( void );


int main( int argc, char *argv[] )
{
    N = 10000;
    if (argc>1)
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

