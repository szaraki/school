#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define True 1
#define False 0


int det(int matrix[3][3]) {
	
	return 	  matrix[0][0]* matrix[1][1] * matrix[2][2]
			+ matrix[1][0]* matrix[2][1] * matrix[0][2]
			+ matrix[2][0]* matrix[0][1] * matrix[1][2]
			- matrix[2][2]* matrix[1][1] * matrix[0][0]
			- matrix[0][2]* matrix[2][1] * matrix[1][0]
			- matrix[1][2]* matrix[0][1] * matrix[2][0];
}




int main(){
	srand(time(NULL));

	
	int matrix[3][3] = {{0,0,0},{0,0,0},{0,0,0}};	
	for (int pos0 = 0; pos0 < 3; pos0+=1) {
		for (int pos1 = 0; pos1 < 3; pos1+=1) {
			matrix[pos0][pos1] = rand()%11;
		}		
	}
	
	int d = det(matrix);
	
	
	return 0;
}