#include <stdio.h>
#include <math.h>

void roots(int a[3]) {
	
	if( a[0] == ){
		if (a[1] != 0) {
			printf("Root: %lf\n",(double)(a[2])/a[1]);
		}
		else {
			printf("Don't have roots\n");
		}
	}
	else {
		double d = sqrt(a[1]*a[1] - 4*a[0]*a[2]);
		if (d>=0) {
			printf("d: %d\n",(int)d);
			printf("First root: %lf\n",(double)(-a[1]-d)/(a[0]*2));
			printf("Second root: %lf\n",(double)(-a[1]+d)/(a[0]*2));
		}
		else {
			printf("Don't have roots\n");
		}
	}
}



int main() {
	int n[3]= {1,2,1};
	roots(n);
	
	
	
}