if(s==0)
	{
		printf("Result verified! :)\n\n");
		printf("Original Matrix Eigenvalues\n");
		int alpha,s1;
		double z[n];
		FILE *fptrk;
		fptrk = fopen("keys", "r");
		fscanf(fptrk,"%d",&alpha);
		fscanf(fptrk,"%d",&s1);
		for(i=0;i<n;i++)
		{
			fscanf(fptr,"%lf",&z[i]);
			double ans=(z[i]-s1)/alpha;
			printf("%lf\t",ans);
		}
		printf("\n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				fscanf(ft,"%lf",&transpose[i][j]);
			}
		}
		printf("\nEigenVectors of Original Matrix\n");
		k=-1;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				double s2=0.00;
				if(i==0)
				{
					if(transpose[i][n-1]==1.00){s2=s2+vectors[n-1][j];}
					else if(transpose[i][n-1]==-1.00){s2=s2-vectors[n-1][j];}
					else{printf("This is fuck\n");}
				}
				else
				{
					if(transpose[i][k]==1.00){s2=s2+vectors[k][j];}
					else if(transpose[i][k]==-1.00){s2=s2-vectors[k][j];}
					else{printf("This is fuck\n");}
				}
				finalvec[i][j]=s2;
				printf("%lf\t",finalvec[i][j]);
			}
			k=k+1;
			printf("\n");
		}
	}
	else
	{
		printf("Result obtained is wrong :(\n");
	}
	fclose(fp);
	fclose(fptr);
	fclose(fpt);
	fclose(ft);
	printf("\n");
	cpu_time_used = (double) (end - start)/(double)(CLOCKS_PER_SEC);
      	printf("Running time of code is %lf\n\n",cpu_time_used);
	return 0;
}
