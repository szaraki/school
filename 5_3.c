#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0



int** matrix_mul(int matrix[2][2][2]){
	
	
	//create result dynamic list
	const int MAX = 2;
	int** result= malloc( MAX* sizeof(int*));
	if (result == NULL) {
		return NULL;
	}
	for ( int x =0; x < MAX; x+=1) {
		result[x] = malloc( MAX* sizeof(int));
		if (result[x] == NULL) {
			return NULL;
		}
		for ( int y =0; y < MAX; y+=1) {
			result[x][y] = 0;
		}
	}
	
	/*
	matrix 	00 01
			10 11
			-----
	  00 01|00 01
	  10 11|10 11
	*/
	for ( int pos0 = 0; pos0 < 2; pos0+=1) {
		for ( int pos1 = 0; pos1 < 2; pos1+=1) {
			for ( int pos2 = 0; pos2 < 2; pos2+=1) {
				result[pos0][pos1] += matrix[0][pos2][pos0]*matrix[1][pos1][pos2];
			}
		}
	}	
	
	return result;
	
}




int main(){
	
	
	
	
	
	return 0;
}