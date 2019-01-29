#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include<lapacke.h>
extern void LAPACK_dgeev( char* jobvl, char* jobvr, int* n, double* a, int* lda, double* wr, double* wi, double* vl, int* ldvl, double* vr, 
int* ldvr, double* work, int* lwork, int* info );
extern void print_eigenvalues( char* desc, int n, double* wr, double* wi );
extern void print_eigenvectors( char* desc, int n, double* wi, double* v,int ldv );

double a[2048*2048];
double wr[2048*2048],wi[2048*2048],vl[2048*2048],vr[2048*2048];
double* work;
int N,LDA,LDVL,LDVR;
int n, lda, ldvl, ldvr, info, lwork;
FILE *fptr;
FILE *fpt;
FILE *fp;
int main() 
{
	clock_t start, end;
    	double cpu_time_used;
    	start = clock();
    	fptr = fopen("matrix", "r");
    	fpt = fopen("valueseigen", "w");
    	fp = fopen("vectors","w");
	fscanf(fptr,"%d",&N);
	LDA=N; LDVL=N; LDVR=N;
        n = N; lda = LDA; ldvl = LDVL; ldvr = LDVR;
        int i,j,k=0;
        double wkopt;
	for(int i=0;i<LDA*N;i++)
	{
	  double temp;
	  fscanf(fptr,"%lf",&temp);
	  a[i]=temp;
	}
        lwork = -1;
        LAPACK_dgeev( "Vectors", "Vectors", &n, a, &lda, wr, wi, vl, &ldvl, vr, &ldvr, &wkopt, &lwork, &info );
        lwork = (int)wkopt;
        work = (double*)malloc( lwork*sizeof(double) );
        // Solve eigenproblem
        LAPACK_dgeev( "Vectors", "Vectors", &n, a, &lda, wr, wi, vl, &ldvl, vr, &ldvr, work, &lwork, &info );
        //Check for convergence
        if( info > 0 ) 
        {
                printf( "The algorithm failed to compute eigenvalues.\n" );
                exit( 1 );
        }
        //Print eigenvalues
        print_eigenvalues( "Eigenvalues", n, wr, wi );
        //Print eigenvectors
        print_eigenvectors( "Right eigenvectors", n, wi, vl, ldvl );
        //Free workspace
        free((void*)work);
        fclose(fptr);
        fclose(fpt);
        fclose(fp);
	end = clock();
      	cpu_time_used = (double) (end - start)/(double)(CLOCKS_PER_SEC);
      	printf("Running time of code is %lf\n",cpu_time_used);
        exit( 0 );
}

/* Printing eigenvalues */
void print_eigenvalues( char* desc, int n, double* wr, double* wi ) 
{
   int j;
   for( j = 0; j < n; j++ ) {
      if( wi[j] == (double)0.0 )
      {
	 fprintf(fpt,"%lf ",wr[j]);	 
      }
      else
      {
	 fprintf(fpt,"%lf ",wr[j]);
	 fprintf(fpt,"%lf ",wi[j]);
      }
   }
}

/* Printing eigenvectors */
void print_eigenvectors( char* desc, int n, double* wi, double* v, int ldv ) 
{
   int i, j;
   for( i = 0; i < n; i++ ) 
   {
      j = 0;
      while( j < n )
      {
         if( wi[j] == (double)0.0 ) 
         {
            fprintf(fp,"%lf ",v[i+j*ldv]);
            j++;
         } 
         else
         {
            fprintf(fp,"%lf ",v[i+j*ldv]);
            fprintf(fp,"%lf ",v[i+(j+1)*ldv]);
            
            fprintf(fp,"%lf ",v[i+j*ldv]);
            fprintf(fp,"%lf ",-v[i+(j+1)*ldv]);
            j += 2;
         }
      }
   }
}
