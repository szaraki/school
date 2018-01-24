#include <stdio.h>
#include <stdlib.h>
#include <time.h>




void print_num(int num, int day_now) {
	if( num == day_now) {
		printf("** ");
	}
	else {
		if( num< 10) {
			printf(" %d ", num);
		}
		else {
			printf("%d ", num);
		}
	}
}

int main(){
	
	//init
	time_t time_int;
	time(&time_int);
	
	struct tm* time_struct;
	time_struct = localtime(&time_int);
	
	static const char mon[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
					"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	int day_first= (time_struct->tm_wday+ 6+ time_struct->tm_mday+ 1)% 7;
	int wday_now= (time_struct->tm_wday+6)%7;
	
	
	//print month name
	printf("%s\n", mon[time_struct->tm_mon]);
	
	//print space to first day
	for(int n=0; n< day_first; n+=1) {
		printf("   ");
	}
	
	//print month day
	for (int day= 1; day < 31; day+=1) {
		print_num(day, time_struct->tm_mday);
		if ((day+ day_first)%7 == 0) {
			printf("\n");
		}
	}
	printf("\n");
	
	return 0;
}