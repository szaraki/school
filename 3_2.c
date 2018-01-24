#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define True 1
#define False 0



double f2c(double fahrenheit) {
	const double f2c_static =5./9.;
	return (fahrenheit-32.)*f2c_static;
}


double c2f(double celsius) {
	const double c2f_static =9./5.;
	return celsius*c2f_static + 32.;
}




int main(){
	
	
	
	
	
	return 0;
}