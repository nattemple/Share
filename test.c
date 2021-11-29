#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define alpha( i,j ) A[ (j)*ldA + i ]   // map alpha( i,j ) to array A
#define chi( i )  x[ (i)*incx ]         // map chi( i )  to array x
#define psi( i )  y[ (i)*incy ]         // map psi( i )  to array y


/* RandomMatrix overwrites a matrix with random values */
void RandomMatrix( int, int, double *, int );

//void Axpy( int, double, double *, int, double *, int );
void Axpy( int n, double alpha, double *x, int incx, double *y, int incy )
{
  for ( int i=0; i<n; i++ )
    psi(i)  += alpha * chi( i );   // Fused Multiply-Add
}


/* MyGemv is a common interface to all the implementations we will 
   develop so we don't have to keep rewriting this driver routine. */
//void MyGemv( int, int, double *, int, double *, int, double *, int );
void MyGemv( int m, int n, double *A, int ldA,
           double *x, int incx, double *y, int incy )
{
  for ( int j=0; j<n; j++ )
    Axpy( m, chi( j ), &alpha( 0,j ), 1, y, incy );
}



int main(int argc, char *argv[])
{
  int
    m, n,
    ldA, 
    size;

  double
    *A, *x, *y;

    size=6;

    m = n = size;
    ldA = size;

    A = ( double * ) malloc( ldA * n * sizeof( double ) );
    x = ( double * ) malloc( n * sizeof( double ) );
    y = ( double * ) malloc( m * sizeof( double ) );

    /* Generate random matrix A */
    RandomMatrix( m, n, A, ldA );

    /* Generate random vector x */
    RandomMatrix( n, 1, x, n );

    /* Compute y = A x + y */
    MyGemv( m, n, A, ldA, x, 1, y, 1 );

    #define alpha( i,j ) A[ (j)*ldA + i ]   // map alpha( i,j ) to array A 

    printf("\nA=\n");
    for ( int i=0; i<m; i++ ){
        for ( int j=0; j<n; j++ ){
            printf("%lf ", alpha(i,j));
        }
        printf("\n");
    }

    printf("\nx=\n");
    for ( int i=0; i<n; i++ ){
        printf("%lf", x[i]);
        printf("\n");
    }

    printf("\ny=\n");
    for ( int i=0; i<m; i++ ){
        printf("%lf", y[i]);
        printf("\n");
    }



    /* Free the buffers */
    free( A );
    free( x );
    free( y );

  exit( 0 );
}
