#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define PI 3.14


struct Vec2{
	int x;
	int y;
};

double square(struct Vec2 pos[4]) {
	return pow((double)(pos[0].x-pos[1].x), 2.)+ pow((double)(pos[0].y-pos[1].y), 2.);
}

double rectangle(struct Vec2 pos[4]) {
	int width =sqrt(pow((double)(pos[0].x-pos[1].x), 2.)+ pow((double)(pos[0].y-pos[1].y), 2.));
	int high =sqrt(pow((double)(pos[1].x-pos[2].x), 2.)+ pow((double)(pos[1].y-pos[2].y), 2.));
	
	return width* high;
}

double triangle(struct Vec2 pos[3]) {
	int a =sqrt(pow((double)(pos[0].x-pos[1].x), 2.)+ pow((double)(pos[0].y-pos[1].y), 2.));
	int b =sqrt(pow((double)(pos[1].x-pos[2].x), 2.)+ pow((double)(pos[1].y-pos[2].y), 2.));
	int c =sqrt(pow((double)(pos[2].x-pos[0].x), 2.)+ pow((double)(pos[2].y-pos[0].y), 2.));
	double p = (a+b+c)/2;
	
	return sqrt(p*(p-a)*(p-b)*(p-c));
}

double wheel(int r) {
	return PI*pow((double)r,2.);
}


int main(){
	struct Vec2 sq[4] = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
	struct Vec2 re[4] = {{0, 0}, {10, 0}, {10, 20}, {0, 20}};
	struct Vec2 tr[3] = {{0, 0}, {10, 0}, {10, 10}};
	
	printf("%lf\n", square(sq));
	printf("%lf\n", rectangle(re));
	printf("%lf\n", triangle(tr));
	printf("%lf\n", wheel(4));
	
	return 0;
}
