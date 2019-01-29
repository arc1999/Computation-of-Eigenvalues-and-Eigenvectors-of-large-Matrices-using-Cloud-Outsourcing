#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
double arr[1500][1500];
double m[1500];
double M[1500][1500];
double bij[1500];
double I[1500][1500],Ad[1500][1500],Mt[1500][1500],B[1500][1500],C[1500][1500];
int n;
FILE *fptr;
FILE *fpt;
FILE *fp;
int input()
{
	int i,j,k,dec;
	printf("Enter the order of matrix\n");
	scanf("%d",&n);
	//putw(n, fptr);
	fprintf(fptr,"%d ",n);
	printf("Do you want to enter the elements manually or want to automate this process?\n1 for Manual Entering Elements\n2 for Automating the Process\n");
	scanf("%d",&dec);
	srand(time(0));
	if(dec==1)
	{
		printf("Enter the elements of the matrix\n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				scanf("%lf",&arr[i][j]);
			}
		}
		return 1;
	}
	else if(dec==2)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				arr[i][j]=(rand()%1000)+1;
			}
		}
		return 1;
	}
	else
	{
		printf("Wrong choice\n");
		return 0;
	}
}
void keygen()
{
	int i,j;
	double range[]={-1.0,1.0};
	srand(time(0));
	for(i=0;i<n;i++)
	{
		if(i!=(n-1))
		{
			bij[i]=i+1;
		}
		else
		{
			bij[i]=0;
		}
	}
	for(i=0;i<n;i++)
	{
		int u=rand()%2;
		m[i]=range[u];
		
		for(j=0;j<n;j++)
		{
			if(bij[i]==j)
			{
				M[i][j]=m[i];
			}
			else
			{
				M[i][j]=0.00;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%lf\t",M[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
