#include <stdio.h>
#include <time.h>

#define True 1
#define False 0


int check_input(int t1[3], int t2[3]) {
	return  t1[0]>=0&& t1[0]<24&& t2[0]>=0&& t2[0]<24&& /* Hour */
			t1[1]>=0&& t1[1]<60&& t2[1]>=0&& t2[1]<60&& /* Minutes */
			t1[2]>=0&& t1[2]<60&& t2[2]>=0&& t2[2]<60;	/* Seconds */
	
}


int compare(int t1[3],int t2[3]) {
	/* FUNCTION OPTIMALISED FOR NON THE SAME TIMES*/
	/* output:
		-2	, bad input
		-1	, t1 > t2
		0	, t1 == t2
		1	, t2 > t1
	*/	
	
	
	if( check_input(t1, t2) == False) {
		return -2;
	}
	
	for (int pos = 0; pos < 3; pos+=1) {
		if (t1[pos] > t2[pos]){
			return -1;
		}
		if (t2[pos] > t1[pos]){
			return 1;
		}		
	}		
	return 0;
}

int main(){
	
	
	
	
	
	return 0;
}