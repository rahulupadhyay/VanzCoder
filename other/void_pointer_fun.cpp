#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** args)
{

	int var1 = 1;
	char var2 = 'V';
	void* voidPointerChar = &var2;
	void* voidPointerInt = &var1;

	if(voidPointerChar == &var2){
		printf("voidPointerChar == &var2\n");
	}
	if(voidPointerInt == &var1){
		printf("voidPointerInt == &var1\n\n");
	}

	if(*((char*)voidPointerChar) == var2){
		printf("*(char)voidPointerChar == &var2\n");
	}
	if(*((int*)voidPointerInt) == var1){
		printf("*(int)voidPointerInt == &var1\n\n");
	}
	printf("voidPointerInt = %d\n", voidPointerInt);
	printf("voidPointerChar = %d\n\n", voidPointerChar);
	printf("&voidPointerInt = %d\n", &voidPointerInt);
	printf("&voidPointerChar = %d\n\n", &voidPointerChar);


	printf("int var1 = %d\n", var1);
	printf("char var2 = %c\n\n", var2);
	printf("int &var1 = %d\n", &var1);
	printf("char &var2 = %d\n", &var2);
}


