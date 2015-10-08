#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void generateObservationMatrix(int O[81][4], int res[81])
{
	/* Variables used for computing the observation matrix */
	int i,j,unit,tens,hundreds,thousands;

	j = unit = tens = hundreds = thousands = 0;
	
	// This portion of code finds all possible comibnation for O = {O1, O2, O3, O4} where O belongs to (0,1,2)
	for(i=0;i<2223;i++)
	{
		if(i<10)
		{
		unit = i%10;
		}
		else if(i>=10 & i<100)
		{
		unit = i%10;
		tens = i/10;
		tens = tens%10;
		}
		else if(i>=100 & i<1000)
		{
		unit = i%10;
		tens = i/10;
		tens = tens%10;
		hundreds = i/100;
		hundreds = hundreds%10;
		}
		else if(i>=1000 & i<2223)
		{
		unit = i%10;
		tens = i/10;
		tens = tens%10;
		hundreds = i/100;
		hundreds = hundreds%10;
		thousands = i/1000;
		thousands = thousands%10;
		}
		if ( unit < 3 && tens < 3 && hundreds < 3 && thousands < 3 )
		{
			// printf("\nValue of i is : %4d. Value of j is : %d",i,j);
			res[j] = i;
			j++;
		}
	}
	
	// This portion builds the observation matrix and prints it
	
	// printf("\n\n\nThis is the final observation state matrix.\n\n\t\tO1\tO2\tO3\tO4\n");
	for(i=0;i<81;i++)
	{
			if( res[i] < 10 )
			{
				O[i][0] = 0;
				O[i][1] = 0;
				O[i][2] = 0;
				O[i][3] = res[i];
			}
			else if( res[i] >= 10 && res[i] < 100 )
			{
				O[i][0] = 0;
				O[i][1] = 0;
				O[i][2] = res[i]/10;
				O[i][3] = res[i]%10;
			}
			else if( res[i] >= 100 && res[i] < 1000 )
			{
				O[i][0] = 0;
				O[i][1] = res[i]/100;
				O[i][2] = (res[i]/10)%10;
				O[i][3] = res[i]%10;
			}
			else if( res[i] >= 1000 && res[i] < 2223 )
			{
				O[i][0] = res[i]/1000;
				O[i][1] = (res[i]/100)%10;
				O[i][2] = (res[i]/10)%10;
				O[i][3] = res[i]%10;
			}
			
			// printf("Row No %d 	%d 	%d 	%d 	%d 	\n",i+1,O[i][0],O[i][1],O[i][2],O[i][3]);
	}
	
}

float computeAlphaPass(int noOfStates, int noOfObservations, int rowInOMatrix, int O[81][4], float PI[2], float A[2][2], float B[2][3] )
{
	int N,T,i,j,t;
	float a[noOfObservations][noOfStates], tempResult;
	N = noOfStates;
	T = noOfObservations;
	tempResult = 0.0;
	
	// Compute a(0)[i] (Alpha subscript 0)
	for (i=0;i<N;i++)
		{
			a[0][i] =  PI[i] * B[i][O[rowInOMatrix][0]];
			// printf("\nValue of a[0][%d] : %f", i,a[0][i]);
		
		}

	// Compute a(1)[i] .... a(T-1)[i]
	for(t=1;t<T;t++)
	{
		for(i=0; i <= N-1; i++)
		{
			a[t][i] = 0.0;
			for(j=0; j <= N-1; j++)
			{
				a[t][i] = a[t][i] + ( a[t-1][j] * A[j][i] );
			}
			a[t][i] = a[t][i] * B[i][O[rowInOMatrix][t]] ;
			// printf("\nValue of a[%d][%d] : %f", t,i,a[t][i]);
		}
	}
//	printf("\nValue of a[%d][0] : %f\t\tValue of a[%d][1] : %f\t\t SUM = %f", T-1,a[T-1][0],T-1,a[T-1][1],a[T-1][0]+a[T-1][1]);
	for(i=0; i <= N-1; i++)
	{
		tempResult += a[T-1][i];
	}

	printf("\nResult computed using alpha pass algorithm for observation sequence O=(%d,%d,%d,%d) is : %f\n\n", O[rowInOMatrix][0], O[rowInOMatrix][1], O[rowInOMatrix][2], O[rowInOMatrix][3], tempResult);
	
	return (tempResult);
	
}

float computeUsingNaiveApproach(float A[2][2], float B[2][3], float PI[2], int O[81][4], char states[16][4], float sumAcrossObservation[81][1])
{
	/* Variables used for computing the Probabilities for each observation */
	int currentState, nextState, currentObservation, oi,oj,si,i,j;
	float PIx0,  biO, transition, result, sumOfProbabilities;
	sumOfProbabilities = 0.0;
	char x0 = ' ';
	result = 1.0;
	float finalResult[16][81];

	for (oi=0;oi<81;oi++) /* This loop variable iterates over the rows of the Observation Matrix O[81][4] */
	{
		
		for (si=0;si<16;si++) /* This loop variable iterates over the rows of the States Matrix states[4][4] */
		{
			x0 = states[si][0]; /* This variable holds x0 for each observation sequence */
		
			if( x0 == 'H' )
				PIx0 = PI[0]; 
			else
				PIx0 = PI[1];
	
			
			for (oj=0;oj<4;oj++) /* This loop variable iterates over the columns of the Observation Matrix O[81][4] */
			{
					
					if( states[si][oj] == 'H' )
						currentState = 1;
					else
						currentState = 0;
					
				// Get the next state in the chain
				if(oj < 3)
				{
					if( states[si][oj+1] == 'H' )
						nextState = 1;
					else if(states[si][oj+1] == 'C')
						nextState = 0;
				
					if( currentState == 1 && nextState == 1 ) /* Transition from 'H' to 'H' */
						transition = A[0][0];
					else if( currentState == 1 && nextState == 0 ) /* Transition from 'H' to 'C' */
						transition = A[0][1];
					else if( currentState == 0 && nextState == 1 ) /* Transition from 'C' to 'H' */
						transition = A[1][0];
					else if( currentState == 0 && nextState == 0 ) /* Transition from 'C' to 'C' */
						transition = A[1][1];
				}
					// printf("\nCurrent State is : %d		Next State is : %d		\n",currentState,nextState);
				
				
					currentObservation = O[oi][oj]; /* This variable will coresspond to the column in the B matrix*/
				
					if( currentState == 1 ) /* Current State is H --> Coressponds to Row 0 in the B matrix */
						biO = B[0][currentObservation]; 
					else if( currentState == 0 ) /* Current State is C --> Coressponds to Row 1 in the B matrix */
						biO = B[1][currentObservation];
			
					if ( oj == 0 )
					{	
						result = result * PIx0*biO*transition;
						// printf("\n The value if i is : %d     The value of j is : %d   The value of PIX0 is : %f    The value of biO is : %f   The value of transition is : %f   The value of result is : %f  \n",oi,oj,PIx0,biO,transition,result);
					}
					else
					{
						if ( oj < 3 )
						{
							result = result * transition*biO;	
							// printf("\n The value if i is : %d     The value of j is : %d   The value of transition is : %f    The value of biO is : %f   The value of result is : %f  \n",oi,oj,transition,biO,result);
						}
						else
						{
							result = result * biO;	
							// printf("\n The value if i is : %d     The value of j is : %d    The value of biO is : %f   The value of result is : %f  \n",i,j,biO,result);
						}
					}
				
			}
			finalResult[si][oi] = result;
			result=1.0;
			// printf("\nStart of new State matrix : %d\n", si);
			// printf("STATES[0][0] : %c",states[0][0]);
		}
	}
	
	/* This part prints the values of the Probabilities computed for each observation sequence for each possible state */
	j=0;
	
	while(j<81)
	{
		sumAcrossObservation[j][0] = 0.0;
//		printf("\n\nSTATES 		PROBABILITIES\tFOR OBSERVATION SEQUENCE : O(%d,%d,%d,%d) \n----------------------------------------------------------------------\n",O[j][0],O[j][1],O[j][2],O[j][3]);
		for(i=0;i<16;i++)
		{
	//		printf("\n%c%c%c%c",states[i][0],states[i][1],states[i][2],states[i][3]);
	
		//	printf(" 		%f ",finalResult[i][j]);
			sumAcrossObservation[j][0] += finalResult[i][j];
		
		}
		//printf("\nSUM ACROSS ALL STATES FOR OBSERVATION SEQUENCE : O(%d,%d,%d,%d) : %f ", O[j][0],O[j][1],O[j][2],O[j][3], sumAcrossObservation[j][0]);
		j++;
	}
	
	/* This part computes the sum of all the given probabilities to show that they add up to 1.0*/
	//for(i=0;i<16;i++)
	//{
		for(j=0;j<81;j++)
		{
			sumOfProbabilities = sumOfProbabilities + sumAcrossObservation[j][0];
		}
		
	//} 
	
	//printf("\n\n\nSum of all probabilities across all states computed using naive approach is : %f\n\n",sumOfProbabilities);
	return (sumOfProbabilities);
}

int main()
{
	
	/* This is the state transition matrix */
	float A[2][2] = { 
	{0.7,0.3}, 
	{0.4,0.6} 
	};
	
	/* This is the observation matrix */
	float B[2][3] = {
		{0.1,0.4,0.5},
		{0.7,0.2,0.1}
	};
	
	/* This is the PI(Initial State) matrix*/
	float PI[2] = {0.6,0.4};
	
	/* This matrix gives the various possible hidden states */ 
	char states[16][4] = {	
	{'H','H','H','H'},		
	{'H','H','H','C'},		
	{'H','H','C','H'},		
	{'H','H','C','C'},
	{'H','C','H','H'},
	{'H','C','H','C'},
	{'H','C','C','H'},
	{'H','C','C','C'},
	{'C','H','H','H'},
	{'C','H','H','C'},
	{'C','H','C','H'},
	{'C','H','C','C'},
	{'C','C','H','H'},
	{'C','C','H','C'},
	{'C','C','C','H'},
	{'C','C','C','C'}
	};

	/* Variables used for computing the observation matrix */
	int i, O[81][4], res[81];

	/* Variables used for computing the Probabilities for each observation */
	int currentState, nextState, currentObservation, oi,oj,si,t;
	float PIx0,  biO, transition ;
	float result[81][1] = {0.0};
	float sumOfProbabilitiesForwardAlgo, sumOfProbabilitiesNaiveAlgo;
	float sumAcrossObservation[81][1] = {0};
	int noOfStates, noOfObservations;
	int counter = 0;
	noOfStates = 2;
	noOfObservations = 4;
	sumOfProbabilitiesForwardAlgo = sumOfProbabilitiesNaiveAlgo = 0.0;
	
	// Generate all possible values for the observation matrix
	generateObservationMatrix(O, res);

	// Compute probabilities using alpha pass algorithm for all possible observations
	for(i=0;i<81;i++)
	{	
		result[i][0] = computeAlphaPass(noOfStates, noOfObservations, i, O, PI, A, B);
		sumOfProbabilitiesForwardAlgo += result[i][0];
	}

	printf("\n\nThe sum of all probabilities calculated using Alpha Pass algoriithm is : %f.\n", sumOfProbabilitiesForwardAlgo);
	
	// Compute probabilities using naive approach for all possible observations and calculate the sum of all probabilities
	sumOfProbabilitiesNaiveAlgo = computeUsingNaiveApproach(A, B, PI, O, states, sumAcrossObservation);
	
	printf("\n\nThe sum of all probabilities calculated using Naive approach is : %f.\n", sumOfProbabilitiesNaiveAlgo);
	
	// Below Code checks if results obtained from Naive approach and Forward Algorithm match each other
	
	for(i=0;i<81;i++)
	{	
		if ( roundf((result[i][0] * 1000000)/1000000) == roundf((sumAcrossObservation[i][0] * 1000000)/1000000))
		{	
			printf("\n VALUE COMPUTED USING NAIVE APPROACH %f MATCHES WITH VALUE COMPUTED BY FORWARD ALGORITHM : %f FOR OBSERVATION SEQUENCE : O(%d,%d,%d,%d)", sumAcrossObservation[i][0], result[i][0], O[i][0],O[i][1],O[i][2],O[i][3]);
			counter++;
		}
		else
			printf("\n VALUE COMPUTED USING NAIVE APPROACH %f DOES NOT MATCH WITH VALUE COMPUTED BY FORWARD ALGORITHM : %f FOR OBSERVATION SEQUENCE : O(%d,%d,%d,%d)", sumAcrossObservation[i][0], result[i][0], O[i][0],O[i][1],O[i][2],O[i][3]);
	}
	
	if (counter == 81)
		printf("\nNo of correct matches : %d\n\nThe program has terminated successfully.\n\n",counter);
	else
		printf("\nNo of values that do not match : %d\n\n",81-counter);
	
	return 0;
}
