/*
 *This source contains stack implementation functions
 * */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stackNode{
	int value;
	char charValue;
	struct stackNode *nextNode;
};

typedef struct stackNode stackElement;
typedef stackElement *stackElmtPointer;

void invertWords();
void push(stackElmtPointer,stackElmtPointer);
stackElmtPointer pop(stackElmtPointer);
int isEmpty(stackElmtPointer);
void printStack(stackElmtPointer);


int main(void){
	invertWords();
	return 0;
}


void invertWords()
{
	printf("Give a sentence: ");
	char sentence[100];
	scanf("%s",sentence);
	stackElmtPointer stack = NULL;
	int index;
	for(index = 0; index < strlen(sentence);index++){
		stackElmtPointer newNode = malloc(sizeof(stackElement));
		newNode->charValue = sentence[index];
		newNode->nextNode = NULL;
		push(stack,newNode);
	}
	printStack(stack);
	printf("\nThe word on the invert order is: ");
	while(!isEmpty(stack)){
		char letter = pop(stack)->charValue;
		printf("%c",letter);
	}
}

/*
 *This function push a new element on the top of stack
 * FIXME - This function doesn't work how expected
 * */
void push(stackElmtPointer stack, stackElmtPointer element)
{
	if(!isEmpty(stack)){
		element->nextNode = stack;
		stack = element;
	}else{
		element->nextNode = NULL;
		stack = element;
	}
}

/*
 *This function remove ( pop ) the top element of the stack
 * */
stackElmtPointer pop(stackElmtPointer stack)
{	
	if(isEmpty(stack)){
		stackElmtPointer tempStack = stack->nextNode;
		stackElmtPointer top = stack;
		top->nextNode = NULL;
		stack = tempStack;
		return top;
	}
	return NULL;
	
}

int isEmpty(stackElmtPointer stack)
{
	return stack == NULL;
}

void printStack(stackElmtPointer stack)
{	
	printf("STACK = ");
	if(!isEmpty(stack)){
		printf("TOP -> ");
		stackElmtPointer currentStack = stack;
		while(currentStack != NULL){
			printf("%d/%c -> ", currentStack->value,currentStack->charValue);
			currentStack = currentStack->nextNode;
		}
	}
	printf("NULL");
}


