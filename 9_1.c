#include <stdio.h>
#include "clipboard.h"

#define True 1
#define False 0



int main() {
	set("test2");
	printToStdout();
	append("t");
	printToStdout();
	printf("%d\n", count());
	clean();
	printf("%d\n", count());
	return 0;
}