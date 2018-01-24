#include <stdio.h>


int fahrenheit2celsius(double fahrenheit) {
	const double f2c_static =5./9.;
	return (fahrenheit-32.)*f2c_static;
}

int celsius2fahrenheit(double celsius) {
	const double c2f_static =9./5.;
	return celsius*c2f_static + 32.;
}

int main(){
	printf("%d\n", fahrenheit2celsius(100));
	printf("%d\n", celsius2fahrenheit(100));
	
	return 0;
}
