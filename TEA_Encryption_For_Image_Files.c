/*
 * Problem_31.c
 *
 *  Created on: Feb 18, 2016
 *      Author: VikashRajaSamuel
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void encryptwithTEA(FILE *input, FILE *output)
{
	// Delta is the magic number
	int delta = 0x9e3779b9;

	// Prepare a key to be used
	int K[] = {2147483646, 2147483645, 2147483644, 2147483643};

	int L = 0, R = 0, i, sum;

	// Skipping the first 10 blocks as per requirement
	for( i = 0 ; i < 640 ; i++)
	{
		putc(fgetc(input),output);
	}

	while (!feof(input))
	{
		sum = 0;
		// Read the 64 bits of plain text into L and R blocks
		fread( (void*)&L, 4, 1, input );
		fread( (void*)&R, 4, 1, input );
		// Perform 32 rounds
		for (i = 1; i < 33; i++)
		{
			sum += delta;
			L += ((R<<4)+K[0])^(R+sum)^((R>>5)+K[1]);
		    R += ((L<<4)+K[2])^(L+sum)^((L>>5)+K[3]);
		}
		// Write the cipher text to the output
		fwrite( (void*)&L, 4, 1, output );
		fwrite( (void*)&R, 4, 1, output );
	}

	fclose(input);
	fclose(output);

	printf("\n\nTEA encryption has been completed.\n\n");
}

int main()
{
	printf("\n\nThe input BMP file is in the below path : \n%s","D:\\GRADUATE SCHOOL\\SJSU CS\\CS265\\Assignments\\Assignment 3\\alice.bmp");
	printf("\n\nThe encrypted output BMP file is in the below path : \n%s","D:\\GRADUATE SCHOOL\\SJSU CS\\CS265\\Assignments\\Assignment 3\\alice_bmp_encrypted.bmp");

	printf("\n\nThe input JPEG file is in the below path : \n%s","D:\\GRADUATE SCHOOL\\SJSU CS\\CS265\\Assignments\\Assignment 3\\alice.jpg");
	printf("\n\nThe encrypted output JPEG file is in the below path : \n%s","D:\\GRADUATE SCHOOL\\SJSU CS\\CS265\\Assignments\\Assignment 3\\alice_jpg_encrypted.bmp");

	// Specify the input and output file paths here
	FILE * inputBmpFile = fopen("D:\\GRADUATE SCHOOL\\SJSU CS\\CS265\\Assignments\\Assignment 3\\alice.bmp","rb");
	FILE * outputBmpFile = fopen("D:\\GRADUATE SCHOOL\\SJSU CS\\CS265\\Assignments\\Assignment 3\\alice_bmp_encrypted.bmp","wb");
	FILE * inputJpegFile = fopen("D:\\GRADUATE SCHOOL\\SJSU CS\\CS265\\Assignments\\Assignment 3\\alice.jpg","rb");
	FILE * outputJpegFile = fopen("D:\\GRADUATE SCHOOL\\SJSU CS\\CS265\\Assignments\\Assignment 3\\alice_jpg_encrypted.jpg","wb");

	printf("\nStarting TEA encryption for BMP file.");
	encryptwithTEA(inputBmpFile, outputBmpFile);
	printf("\nStarting TEA encryption for JPEG file.");
	encryptwithTEA(inputJpegFile, outputJpegFile);

	return 0;
}

