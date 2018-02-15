#include <stdio.h>
#include "clipboard.h"

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
