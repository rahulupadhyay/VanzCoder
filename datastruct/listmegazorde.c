/*
 *The source contais a lot os functions manipulating list
 *
 * */
#include<stdio.h>

struct node
{
	int value;
	struct node *nextNode;
};

typedef struct node ListNode;
typedef ListNode *nodePointer;


int concateList(nodePointer,nodePointer);
int mixListSort(nodePointer,nodePointer);
void printList(nodePointer);
int isEmpty(nodePointer);

int main(void)
{
	nodePointer startNode = NULL;
	nodePointer startNodeTwo = NULL;

	startNode = malloc(sizeof(ListNode));	
	if(startNode != NULL){
		startNode->value = 1;
		nodePointer scdNode = malloc(sizeof(ListNode));
		scdNode->value = 5;
		scdNode->nextNode = NULL;
		startNode->nextNode = scdNode;
	}
	printList(startNode);

	startNodeTwo = malloc(sizeof(ListNode));
	if(startNodeTwo != NULL){
		startNodeTwo->value = 9;
		nodePointer scdNode = malloc(sizeof(ListNode));
		scdNode->value = 2;
		scdNode->nextNode = NULL;
		startNodeTwo->nextNode = scdNode;
	}
	printList(startNodeTwo);

	concateList(startNode, startNodeTwo);
	printList(startNode);
	return 0;
}

/**
 *This function contace the second list on the first one.
 *
 * */
int concateList(nodePointer mainList, nodePointer secondList)
{
	nodePointer currentNode = mainList;
	nodePointer tempNode;
	
	if(currentNode != NULL){
		while(currentNode->nextNode != NULL){
			currentNode = currentNode->nextNode;
		}
		if(secondList != NULL){
			currentNode->nextNode = secondList;
		}
	}

}

/**
 * This function mix the second list on the first one. The elements are insert in order
 *
 * */
int mixListSort(nodePointer firstList, nodePointer secondList)
{
	if(firstList != NULL){
		
	}
}


/*
 *The function verify if a list is empty
 * */
int isEmpty(nodePointer list)
{
	return list == NULL;
}

/*
 *Print all elements of the list
 * */
void printList(nodePointer list)
{
	nodePointer currentNode = list;
	if(!isEmpty(list)){
		printf("\nThe list's values are: ");	
		while(currentNode != NULL){
			int value = currentNode->value;
			printf("%d -> ", value);
			currentNode = currentNode->nextNode;
		}
		printf(" NULL");
	}else{
		printf("The list is empty, idiot!");
	}
	printf("\n");
}

