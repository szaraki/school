#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_data(void* data,size_t size) {
	//creating temp array
	char* temp = malloc(size);
	memcpy(temp, data, size);
	
	for( int n= 0; n< size; n++) {
		printf("%x%x", temp[n]/16,temp[n]%16);
	}
	printf("\n");
	free(temp);
}

int main() {
	printf("write size of the data: ");
	int size;
	scanf("%i", &size);
	
	printf("write your data: ");
	char* input = malloc(size*sizeof(char));
	scanf("%s", input );
	
	print_data(input, size);
	free(input);
	
	return 0;
}