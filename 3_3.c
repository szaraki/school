#include <stdio.h>
#include <stdlib.h>


#define PI 3.14


double rad2degrees(double rad) {
	return rad* 180./PI;
}

double degrees2rad(double degrees) {
	return degrees*PI/180.;
}

int main(){
	printf("%lf\n", rad2degrees(100));
	printf("%lf\n", degrees2rad(100));
	
	return 0;
}
