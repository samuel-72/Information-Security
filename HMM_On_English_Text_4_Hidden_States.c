#include <stdio.h>
#include <math.h>
#include <float.h>

#define N 4
#define M 27
#define T 50000


void initialize_PI_A(float PI[N], float A[N][N])
{
	int i,j;
	float randomNo = 0.0;
	float tempRandomNo = 0.0;
	float sum = 0.0;
	float sumAcrossStates[N] = {0};
	srand(time(NULL));

	for(i=0;i<N;i++)
	{

		tempRandomNo = (1.0/rand()) * 10000.0 ;
		randomNo = roundf(tempRandomNo * 1000000) / 1000000;

		if(randomNo <= 0.05 && (i % 2) == 0)	
		{	
			PI[i] = ( roundf( (1.0/N) * 1000000)/ 1000000 ) - randomNo;
			sum += PI[i];
		}
		else if(randomNo <= 0.05 && (i % 2) != 0)	
		{
			PI[i] = ( roundf( (1.0/N) * 1000000)/ 1000000 ) + randomNo;
			sum += PI[i];
		}		
		else if(randomNo > 0.05 && (i % 2) == 0)
		{		
			PI[i] = ( roundf( (1.0/N) * 1000000)/ 1000000 ) - (1.0/(100.0+randomNo));
			sum += PI[i];
		}		
		else if(randomNo > 0.05 && (i % 2) != 0)
		{		
			PI[i] = ( roundf( (1.0/N) * 1000000)/ 1000000 ) + (1.0/(100.0+randomNo));
			sum += PI[i];
		}
			
	}
	// The below part ensures that the sum of probabilities across the row in the PI matrix sums to 1.0	
	if (sum >= 1.0)
		PI[N-1] = PI[N-1] + 1.0 - sum;
	else
		PI[N-1] = PI[N-1] + 1.0 - sum;


	// Initialize the A matrix with values ~ 1.0/N

	for(i=0;i<N;i++)
	{
		sum = 0.0;
		sumAcrossStates[i] = 0.0;
		for(j=0;j<N;j++)
		{		
			tempRandomNo = (1.0/rand()) * 10000.0 ;
			randomNo = ( roundf(tempRandomNo * 1000000) / 1000000 ) + 0.037982;

			if(randomNo <= 0.05 && (i % 2) == 0)	
			{	
				A[i][j] = (float)( roundf( (1.0/N) * 1000000)/ 1000000 ) - randomNo;
				sum += A[i][j]; 			
			}
			else if(randomNo <= 0.05 && (i % 2) != 0)	
			{
				A[i][j] = ( roundf( (1.0/N) * 1000000)/ 1000000 ) + randomNo;
				sum += A[i][j];			
			}		
			else if(randomNo > 0.05 && (i % 2) == 0)
			{		
				A[i][j] = ( roundf( (1.0/N) * 1000000)/ 1000000 ) - (1.0/(100.0+randomNo));
				sum += A[i][j];
			}		
			else if(randomNo > 0.05 && (i % 2) != 0)
			{		
				A[i][j] = ( roundf( (1.0/N) * 1000000)/ 1000000 ) + (1.0/(100.0+randomNo));
				sum += A[i][j];
			}
		}
		sumAcrossStates[i] = sum; 
	}

	// The below part ensures that the sum of probabilities across the row in the A matrix sums to 1.0	
	for(i=0;i<N;i++)
	{
		if (sumAcrossStates[i] >= 1.000000)
			A[i][N-1] = A[i][N-1] + 1.0 - sumAcrossStates[i];
		else
			A[i][N-1] = A[i][N-1] + 1.0 - sumAcrossStates[i];
	}

}


void initialize_B(float B[N][M])
{
	int i,j;
	float hl,sum;
	
	// Generate Random values for B[N][M] where the values should be approximately near 0.037037 (1/27) and the sum of the row should be equal to 1.0
	for(i=0;i<N;i++)
	{
		sum = 0.0;
		for(j=0;j<M;j++)
		{ 
			
			if(j<=12)
			{
				hl = 60.0 * (j+1);
				B[i][j] = ( ( roundf( (1.0/M) * 1000000)/ 1000000 ) - ( 1.0/hl ) );
				sum += B[i][j];
				// printf("\nValue of B[%d][%d] is : %f.\tValue of sum is : %f. Value of hl is : %f.\n",i,j,B[i][j],sum,hl);
			}
			else if (j>=13 && j<=25)
			{
				hl = 60.0 * (j-12);
				B[i][j] = ( ( roundf( (1.0/M) * 1000000)/ 1000000 ) + ( 1.0/hl ) );
				sum += B[i][j];
				// printf("\nValue of B[%d][%d] is : %f.\tValue of sum is : %f. Value of hl is : %f.\n",i,j,B[i][j],sum,hl);
			}
			else
			{
				B[i][j] = 1-sum;
				sum += B[i][j];
				// printf("\nValue of B[%d][%d] is : %f.\tValue of sum is : %f.\n",i,j,B[i][j],sum);
				// printf("\nSum of all probabilities in state %d is : %f. Value of j is : %d.\n\n",i,sum,j);
			}
		}
		
	}
	
	
}

void print_A_B_PI(float A[N][N], float B[N][M], float TransposeB[M][N], float PI[N])
{
	int i,j;
	float sumAcrossState[N] = {0};
	float sum = 0;
	char alphabets[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};	

	// Print PI Matrix
	
	printf("\n\nPlease find below the PI matrix.\n\n");
	for(i=0;i<=N-1;i++)
	{
		printf("%f\t",PI[i]);
	}
	
	// Print A Matrix
	
	printf("\n\nPlease find below the A matrix.\n\n");
	for(i=0;i<=N-1;i++)
	{
		for(j=0;j<=N-1;j++)
		{
			printf("%f\t",A[i][j]);
		}
		printf("\n");
	}
	
	
	// Print B Matrix
	
	// Create the Transpose of B matrix and print it
	for(i=0;i<N;i++)
	{
		sum = 0.0;
		for(j=0;j<M;j++)
		{
				TransposeB[j][i] = B[i][j];
				sum += B[i][j];
		}
		sumAcrossState[i] = sum;
	}
	
	// Printing the Transpose of B matrix for better readability
	
	printf("\nLETTER\t");
	for(i=0;i<N;i++)
		printf("STATE[%d]\t\t",i);
	printf("\n");
	for(i=0;i<N;i++)	
		printf("***********************");
	printf("\n");
	
	for(i=0;i<M;i++)
	{
		printf("\n%c",alphabets[i]);
		for(j=0;j<N;j++)
		{
			printf("\t%9f\t",TransposeB[i][j]);
		}

		//printf("\n	");
	}

	printf("\n");
	for(i=0;i<N;i++)	
		printf("------------------------");
	printf("\nSUM");


	for(i=0;i<N;i++)
		printf("\t%9f\t",sumAcrossState[i]);

		printf("\n");
	for(i=0;i<N;i++)	
		printf("------------------------");
	printf("\n\n");

}


void createObservationMatrix(char O[T])
{
	
	FILE *fp1;

	fp1 = fopen("BrownCorpus_50k.txt","r");
	//if (fp1 == NULL)
	//	printf("\nInvalid Path\n");

	int c,i;
	i=0;
	
	while(i<T)
	{
		c = fgetc(fp1);
		
		if (c != EOF )
		{
			O[i++] = c;
		}
		else
		{
			break;
		}
			
	}
	O[T] = '\0';
	fclose(fp1);
	
	// printf("\nThis is the observation matrix\n");
	
	// The part below can be used to verify that the input does not contain anything other than lower case letters and white spaces
	/*
	int k = 0;
	for(i=0;i<T;i++)
	{	
		int j = (int) O[i];
		//printf("%d",j);
		if( j > 96 &&  j < 123 )
			k++;
		else if ( j == 32 || j == 9 || j == 10)
			k++;
		else
			printf("Chara encounterd is : %c", O[i]);
	}
	printf("\nValue of k is : %d.   O[0] is : %c",k,O[0]);
	*/
}

void computeAlphaPass(char O[T], float PI[N], float A[N][N], float B[N][M], float c[T], float a[T][N] )
{
	int i,j,t;
	float tempResult = 0.0;
	
	// Compute a(0)[i] (Alpha subscript 0)
	c[0] = 0 ;
	
	for (i=0;i<N;i++)
	{
		int asciiValue = (int) O[0];
		if( asciiValue > 96 &&  asciiValue < 123 )
			a[0][i] =  PI[i] * B[i][O[0]-97];
		else
			a[0][i] =  PI[i] * B[i][26];
		
		c[0] = c[0] + a[0][i];
		// printf("\nValue of a[0][%d] : %f.\tValue of c[0] is :", i,a[0][i],c[0]);
		// printf("\nValue of O[0] : %c\t%d",O[0],O[0]-97);
		
	}
		
	//Scaling a[0][i]	
	c[0] = 1.0/c[0];
	
	for (i=0;i<N;i++)
	{
		a[0][i] =  c[0]*a[0][i];
		// printf("\nValue of a[0][%d] : %f", i,a[0][i]);
		
	}

	// Compute a(t)[i] .... a(T-1)[i]
	for(t=1;t<T;t++)
	{
		c[t] = 0;
		for(i=0; i <= N-1; i++)
		{
			a[t][i] = 0;
			for(j=0; j <= N-1; j++)
			{
				a[t][i] = a[t][i] + ( a[t-1][j] * A[j][i] );
			}
			
			int asciiValue = (int) O[t];
			if( asciiValue > 96 &&  asciiValue < 123 )
				a[t][i] = a[t][i] * B[i][O[t]-97] ;
			else
				a[t][i] = a[t][i] * B[i][26] ;
			
			c[t] = c[t] + a[t][i];
		//	printf("\nValue of a[%d][%d] : %f", t,i,a[t][i]);
		}
		
		// Scale a[t][i]
		c[t] = 1.0/c[t];
		// printf("\n\nValue of c[%d] is : %f",t,c[t]);
		for(i=0;i<N;i++)
		{
			a[t][i] = c[t]*a[t][i];
			// printf("\nFinal value of a[%d][%d] : %f.",t,i,a[t][i]);
		}
	}
	
	for(i=0; i <= N-1; i++)
	{
		tempResult += a[T-1][i];
	}

	//printf("\nFinal Result : Value of alpha pass for observation sequence O is : %f\n\n", tempResult);
	//printf("\nValue of the scaling factor is : %f %d\n\n",c[t-1],t-1);
	
}


void betaPass (float c[T], float A[N][N],float B[N][M], char O[T], float a[T][N], float b[T][N] )
{
	int i,t,j;
	
	
	for(i=0;i<=N-1;i++)
	{
		b[T-1][i]=c[T-1];
		//printf("\nBeta Value : %f\n",b[T-1][i]);
	}
	
	for(t=T-2;t>=0;t--)
	{
		for(i=0;i<=N-1;i++)
		{
			b[t][i]=0;
			for(j=0;j<=N-1;j++)
			{
				int asciiValue = (int) O[t+1];
				if( asciiValue > 96 &&  asciiValue < 123 )
					b[t][i] = b[t][i] + (A[i][j])*(B[j][asciiValue - 97])*(b[t+1][j]);
				else
					b[t][i] = b[t][i] + (A[i][j])*(B[j][26])*(b[t+1][j]);

			}
			//Scaling BetaT[i] with the same scaling factor as alpha.
			//Scaling b[t][i] with the same factor as a[t][i];
			b[t][i] = c[t] * b[t][i];
		}
	}
	// printf("\nBeta Value : %f %f\n",b[49998][0],b[49998][1]);
	
}

void computegammapass (float c[T], float A[N][N],float B[N][M], char O[T], float a[T][N], float b[T][N], float gamma[T][N], float gamma2[T][N][N] )
{
	float denom;
	int i,j,t;
	
	for (t=0;t<=T-2;t++)
	{
		denom = 0.0;
		for (i=0;i<=N-1;i++)
		{
			for (j=0;j<=N-1;j++)
			{
				int asciiValue = (int) O[t+1];
				if( asciiValue > 96 &&  asciiValue < 123 )
					denom = denom + a[t][i]*A[i][j]*B[j][asciiValue - 97]*b[t+1][j];
				else
					denom = denom + a[t][i]*A[i][j]*B[j][26]*b[t+1][j];
			}
		}
		
		for(i=0;i<=N-1;i++)
		{
			gamma[t][i] = 0;
			for(j=0;j<=N-1;j++)
			{
				int asciiValue = (int) O[t+1];
				if( asciiValue > 96 &&  asciiValue < 123 )
				{	gamma2[t][i][j] = a[t][i] * A[i][j] * B[j][asciiValue - 97] * b[t+1][j]; }
				else
				{
					gamma2[t][i][j] = a[t][i] * A[i][j] * B[j][26] * b[t+1][j];
					if(t==0)
					{
						//printf("\nInside if\n");
						//printf("\nValue of gamma2[%d][%d][%d] : %f. %f %f %f %f %d %d\n",t,i,j,gamma2[t][i][j],a[t][i],A[i][j],B[j][26],b[t+1][j],t+1,j);		
					}

				}
				gamma[t][i] = gamma[t][i] + gamma2[t][i][j];
				
				if(t==0)
				{
					//printf("\nValue of gamma2[%d][%d][%d] : %f.\tValue of gamma[%d][%d] : %f.\n",t,i,j,gamma2[t][i][j],t,i,gamma[t][i]);
					//printf("\nValue of a[%d][%d] : %f.\tValue of B[%d][%d] : %f.\tCharacter at O[%d] : %c. Ascii : %d\n",t,i,a[t][i],j,asciiValue-97,B[j][asciiValue - 97],t+1,O[t+1],asciiValue );
				}
			}
		}
		
	}	

	// Special case for gamma[T-1][i]
	denom = 0.0;
	for(i=0;i<=N-1;i++)
	{
		denom = denom + a[T-1][i];
	}

	for(i=0;i<=N-1;i++)
	{
		gamma[T-1][i] = a[T-1][i]/denom;
	}

	//printf("\nValue of gamma[%d][%d] = %f.\tValue of gamma[%d][%d][%d] = %f.\n",t-1,i-1,gamma[t-1][i-1],t-1,i-1,j-1,gamma2[t-1][i-1][j-1]);
}


void reestimateABPI(float PI[N], float gamma[T][N], float gamma2[T][N][N], float A[N][N], float B[N][M], char O[T])
{
	
	int i,j,t;
	int maxSubscript = 0;
	float numer, denom, sum;
	float sumAcrossStates[N] = {0};		
	float maxValue = 0.000000;

	// Re-estimate PI matrix

	sum = 0.0;

	for(i=0;i<N;i++)	
	{	
		PI[i] = ( ( roundf( gamma[0][i] * 1000000 ) / 1000000 ) >= 0.0 ? ( roundf( gamma[0][i] * 1000000 ) / 1000000 ) : 0.0  );
		PI[i] = ( (PI[i] > 1.000000) ? 1.000000 : PI[i] ) ;
		if (PI[i] < 0.0)
			printf("\nPI[%d] : %f",i,PI[i]);
		sum += PI[i];
	}
	// printf("\n\nPI[3] = %f\tSum : %f",PI[2],sum);
	// Bookkeeping to maintain the sum of all probabilities across the row in PI matrix to 1.0		

	if(sum >= 1.000000)
	{
		for(i=0;i<N;i++)
		{
			if (PI[i] > maxValue)
			{
				maxSubscript = i;
				maxValue = PI[i];
			}
		}
		PI[maxSubscript] = PI[maxSubscript] - (sum-1.000000) ;
			
	}	
	else
	{
		PI[0] = PI[0] + (1.0-sum);
	}
	

	// Re-estimate A matrix

	for(i=0;i<N;i++)
	{
		sum = 0.0;
		sumAcrossStates[i] = 0.0;
		for(j=0;j<N;j++)
		{
				numer = 0.0;
				denom = 0.0;
				for(t=0;t<=T-2;t++)
				{
					numer += gamma2[t][i][j];
					denom += gamma[t][i];
				}
				A[i][j] = ( ( roundf( (numer/denom) * 1000000 ) / 1000000 ) >= 0.0 ? ( roundf( (numer/denom) * 1000000 ) / 1000000 ) : 0.0  );
			
				sum += A[i][j];
		}
		// Bookkeeping to maintain the sum of all probabilities across the row in A matrix to 1.0				

		sumAcrossStates[i] = sum;
		
		if (sumAcrossStates[i] > 1.0)
		{
			for(j=0;j<N;j++)
			{
				if(A[i][j] > 2*(sumAcrossStates[i]-1.0))
				{
					A[i][j] = A[i][j] - (sumAcrossStates[i]-1.0);
					break;
				}
			}
			
		}
		else
		{
			A[i][N-1] = A[i][N-1] + (1.0 - sumAcrossStates[i]);
		}
	}
	
	// Re-estimate B matrix

	for(i=0;i<N;i++)
	{
		sum = 0.0;
		sumAcrossStates[i] = 0.0;
		for(j=0;j<M;j++)
		{
			numer = 0.0;
			denom = 0.0;
			for(t=0;t<=T-1;t++)
			{
				int asciiValue = (int) O[t];
				if( asciiValue > 96 &&  asciiValue < 123 )
				{
					if ( (asciiValue-97) == j )
						numer = numer + gamma[t][i];
				}
				else /* This means that the character is a white space. White space is column no 26(Since array index starts at 0) in the B matrix*/
				{
					if (26 == j)
						numer = numer + gamma[t][i];
				}
				denom = denom + gamma[t][i];
			}

			// Bookkeeping to maintain the sum of all probabilities across the row in B matrix to 1.0		
			B[i][j] = ( ( roundf( (numer/denom) * 1000000 ) / 1000000 ) >= 0.0 ? ( roundf( (numer/denom) * 1000000 ) / 1000000 ) : 0.0  );

			sum += B[i][j];
		}

		// Bookkeeping to maintain the sum of all probabilities across the row in B matrix to 1.0		
		sumAcrossStates[i] = sum;
		if (sumAcrossStates[i] > 1.000000)
		{
			for(j=0;j<M;j++)
			{
				if ( B[i][j] > 2*(sumAcrossStates[i]-1.0) )  
				{
					B[i][j] -= (sumAcrossStates[i]-1.0);
					break;
				}
				//if (B[i][j] < 0.0)
				//	printf("\nB : %f\tSum : %f", B[i][j],(sumAcrossStates[i]-1.0)/( (float) M));

			}
		}		
		else if (sumAcrossStates[i] < 1.000000)
		{
			B[i][j-1] = B[i][j-1] + (1.0 - sumAcrossStates[i]);
		}
	}
	
}

float computeLogP(float c[T])
{
	
	float logProb = 0.0;
	int i;
	
	for(i=0;i<=T-1;i++)
	{
			logProb = logProb + log(c[i]);
	}
	logProb = -logProb;
	
	return logProb;
}


int main()
{

	int maxIters = 200;
	int iters = 0;
	float oldLogProb = -(1.0/0.0);

	/* This is the observation matrix*/
	char O[T] = {' '};

	int i,j;
		
	/* This is the state transition matrix */
	float A[N][N];

/*	float A[N][N] = { 
	{0.47468, 0.52532}, 
	{0.51656, 0.48344} 
	};
*/	
	/* This is the observation matrix and its transpose (For printing the OP)*/
	float B[N][M] = {0};
	float TransposeB[M][N] = {0};
	
	/* This is the PI(Initial State) matrix*/
	float PI[N] = {0};

//	float PI[N] = {0.51316,0.48684};
	
	/* These are the scaling factor, alpha and beta pass matrices*/
	float c[T] = {0};
	float a[T][N] = {0};
	float b[T][N] = {0};
	
	/* These are the gamma and di-gamma matrices*/
	float gamma[T][N] = {0.0};
	float gamma2[T][N][N] = {0.0};
		
	// The below function initializes the PI and A matrices to approximately 1/N
	initialize_PI_A(PI,A);

	// The below function initializes the B matrix to approximately 1/M
	initialize_B(B);

	// Print the initial PI, A and B matrices
	
	printf("\nPlease find below the intial values of the PI, A and B matrices\n\n");
	print_A_B_PI(A, B, TransposeB, PI);
	
	// Get the text in Brown Corpus(First 50000 characters alone) in to the Observation Matrix
	createObservationMatrix(O);

	// Do the initial pass calculations
	
	// Compute Alpha Pass
	computeAlphaPass(O, PI, A, B, c, a );
	
	betaPass(c, A, B, O, a, b );
	
	computegammapass(c, A, B, O, a, b, gamma, gamma2 );

	reestimateABPI(PI,gamma,gamma2,A,B,O);

	printf("\n\nPlease find below the values of PI, A and B matrices after the initial pass.\n---------------------------------------------------------------------------------\n");
	print_A_B_PI(A, B, TransposeB, PI);

	float newLogProb = 0.0;	
	newLogProb = computeLogP(c);
	
	printf("\nValue of Log Prob after initial pass is : %f\n",newLogProb);

	iters += 1;

//	while (iters < maxIters && newLogProb > oldLogProb) //This statement is not used as we reach a local maxima after the 3rd iteration
	while (iters < maxIters)
	{
		oldLogProb = newLogProb;

		computeAlphaPass(O, PI, A, B, c, a );
	
		betaPass(c, A, B, O, a, b );
	
		computegammapass(c, A, B, O, a, b, gamma, gamma2 );

		reestimateABPI(PI,gamma,gamma2,A,B,O);

		newLogProb = computeLogP(c);

		iters++;
	}
	
	printf("\nNo of iterations elapsed : %d.\nCurrent LogProb : %f\t Previous LogProb : %f\n",iters-1,newLogProb,oldLogProb);

	printf("\n\nPlease find below the values of PI, A and B matrices after the final iteration.\n---------------------------------------------------------------------------------\n");
	print_A_B_PI(A, B, TransposeB, PI);

	return 0;
}
