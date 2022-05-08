#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
	Function: matMult 
	Paramaters: 2D integer matricies A, B, C, height and width of matricies
	
	This method multiplies the two matricies A, and B and stores the result in C. 
*/
void matMult(int** C, int** B, int** A, int height, int width){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			for(int k = 0; k < width; k++){
				C[i][j]+= A[i][k] + B[k][j];
			}
		}
	}
}

/*
	Function: matMult2
	Paramaters: 2D integer matricies A, B, C, height and width of matricies
	
	This method multiplies the two matricies A, and B and stores the result in C. Uses loop unrolling of 2. 
*/
void matMult2(int** C, int** B, int** A, int height, int width){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			for(int k = 0; k < width; k+=2){
				C[i][j]+= A[i][k] + B[k][j];
				C[i][j]+= A[i][k+1] + B[k+1][j];
			}
		}
	}
}

/*
	Function: matMult4 
	Paramaters: 2D integer matricies A, B, C, height and width of matricies
	
	This method multiplies the two matricies A, and B and stores the result in C. Uses loop unrolling of 4. 
*/
void matMult4(int** C, int** B, int** A, int height, int width){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			int k = 0;
			for(k; k < width-4; k+=4){
				C[i][j]+= A[i][k] + B[k][j];
				C[i][j]+= A[i][k+1] + B[k+1][j];
				C[i][j]+= A[i][k+2] + B[k+2][j];
				C[i][j]+= A[i][k+3] + B[k+3][j];
			}
			// Because 250 isn't easibly divisible by 4, we need to do the last two adds on their own when k = 248
			C[i][j]+= A[i][k] + B[k][j];
			C[i][j]+= A[i][k+1] + B[k+1][j];
		}
	}
}

/*
	Function: matMult8 
	Paramaters: 2D integer matricies A, B, C, height and width of matricies
	
	This method multiplies the two matricies A, and B and stores the result in C. Uses Loop unrolling of 8. 
*/
void matMult8(int** C, int** B, int** A, int height, int width){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			int k = 0;
			for(k; k < width-8; k+=8){
				C[i][j]+= A[i][k] + B[k][j];
				C[i][j]+= A[i][k+1] + B[k+1][j];
				C[i][j]+= A[i][k+2] + B[k+2][j];
				C[i][j]+= A[i][k+3] + B[k+3][j];
				C[i][j]+= A[i][k+4] + B[k+4][j];
				C[i][j]+= A[i][k+5] + B[k+5][j];
				C[i][j]+= A[i][k+6] + B[k+6][j];
				C[i][j]+= A[i][k+7] + B[k+7][j];
			}
			// Because 250 isn't easibly divisible by 8, we need to do the last two adds on their own when k = 248
			C[i][j]+= A[i][k] + B[k][j];
			C[i][j]+= A[i][k+1] + B[k+1][j];
		}
	}
}

/*
	MatMult - this script generates two matricies of size width*height and filles them with random int values of 0 or 1. 
	You can pass in an arguemnt of 0, 2, 4, 8 to dictate which loop unrolling would like to be done. 

	First the variables are declared and memory allocated, then the A and B arrays are filled with random numbers and C is filled with 
	zeros, then we look at our passed in argument check how much loop unrolling we will do. 
*/
int main(int argc, char* argv[]){
	int height = 250;
	int width = 250;
	int **A = (int**)malloc(height*sizeof(int*));
	int **B = (int**)malloc(height*sizeof(int*));
	int **C = (int**)malloc(height*sizeof(int*));
	for(int i = 0; i<height; i++){
		A[i] = (int*)malloc(width*sizeof(int));
		B[i] = (int*)malloc(width*sizeof(int));
		C[i] = (int*)malloc(width*sizeof(int));
	}

	srand(time(NULL));

	for(int i = 0; i<250; i++){
		for(int j = 0; j<250; j++){
			A[i][j] = rand()%2;
			B[i][j] = rand()%2;
			C[i][j] = 0;
		}
	}
	switch(atoi(argv[1])){
		case 2: matMult2(C, B, A, height, width);
				break;
		case 4: matMult4(C, B, A, height, width);
				break;
		case 8: matMult8(C, B, A, height, width);
				break;
		default:matMult(C, B, A, height, width);
				break;
	}
	return 0;
}