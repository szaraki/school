#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


char* str= NULL;

const int chunkSize = 5;
struct TextChuck {
	char text[chunkSize];
	int size;
	TextChuck *previousChunk;
	TextChuck *nextChunk;
	int readCounter; 
};


static struct TextChuck arr[10];

int set(const char* text) {
	size_t MAX = strlen(text);
	char* try = malloc(MAX*sizeof(char));
	
	if( try==NULL) {
		free(try);
		return false;
	}
	strcpy(try, text);
	free(str);
	str = try;
	return true;
}

int append(const char* text) {
	size_t MAX_OLD = strlen(str);
	size_t MAX = strlen(text) + MAX_OLD+1;
	char* try = malloc(MAX*sizeof(char));
	
	if( try==NULL) {
		free(try);
		return false;
	}
	strcpy(try, str);
	strcpy(try+ MAX_OLD, text);
	free(str);
	str = try;
	return true;
}

int initialise(void) {
	char* try = malloc(1*sizeof(char));
	if( try==NULL) {
		free(try);
		return false;
	}
	strcpy(try, "");
	str = try;
	return true;
}

void clean(void) {
	free(str);
}	

int count(void) {
	return strlen(str);
}

void printToStdout(void) {
	for(char* temp= str; *temp !='\0'; temp+=1) {
		printf("%c", *temp);
	}
	printf("\n");
}