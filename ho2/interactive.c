#include <stdio.h>
#include <stdlib.h>

int main() {
	int a = 0, b = 0;

	printf("Enter 2 numbers: ");
	int c = scanf("%d %d", &a,&b);

	if(c==2) printf("%d + %d = %d\n",a,b,a+b);
	else printf("%d invalid inputs\n",2-c);
	
	printf("%d value(s) read successfully\n",c);
	
	return EXIT_SUCCESS;
}
