/*
 *The source contais a lot os functions manipulating list
 * TODO - Improve all the algorithms. We have repeat code, and the algorithms aren't intelligent
 * */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node
{
	int value;
	struct node *nextNode;
};

typedef struct node ListNode;
typedef ListNode *nodePointer;


void concateList(nodePointer,nodePointer);
nodePointer merge(nodePointer,nodePointer);
void printList(nodePointer);
int isEmpty(nodePointer);
void insertSort(nodePointer,nodePointer);
void optList();
void invertList();
nodePointer createRandomList(int);
void insertList(nodePointer, nodePointer);

int main(void)
{
	invertList();
	return 0;
}
/**
 *This function contace the second list on the first one.
 *
 * */
void concateList(nodePointer mainList, nodePointer secondList)
{
	nodePointer currentNode = mainList;
		
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
 * This function merge two list on a third one. The elements are insert in order
 */
nodePointer merge(nodePointer firstList, nodePointer secondList)
{
	nodePointer newList = NULL;
	nodePointer mergeList = NULL;
	if(firstList != NULL){
		newList = firstList;
		mergeList = secondList;
	}else if(secondList != NULL){
		newList = secondList;
		mergeList = firstList;
	}

	nodePointer tempNode = NULL;
	while(!isEmpty(mergeList)){
		tempNode = mergeList->nextNode;
		mergeList->nextNode = NULL;
		insertSort(newList,mergeList);	
		mergeList = tempNode;
	}
	return newList;
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
		printf(" NULL\n");
	}else{
		printf("\nThe list is empty, idiot!\n'");
	}
}

/**
 *This function insert a element in a list.
 * FIXME - This functions doesn't work how expected with small lists.
 * */
void insertSort(nodePointer list,nodePointer element )
{
	nodePointer currentNode = list;
	nodePointer nextNode = NULL;
	while(currentNode != NULL){
		nextNode = currentNode->nextNode;
		if(nextNode != NULL){
			if((element->value >= currentNode->value) & (element->value <= (currentNode->nextNode)->value)){
				nodePointer tempNode = NULL;
				tempNode = currentNode->nextNode;
				currentNode->nextNode = element;
				element->nextNode = tempNode;
				return;
			}
			currentNode = nextNode;
		}else{
			currentNode->nextNode = element;
			return;
		}
	}

}

/**
 * This function raffle 25 int elements for a list and calculates the sum and average for it.
 */
void optList()
{
	nodePointer list = NULL;
	int index;
	srand(time(NULL));
	list = malloc(sizeof(ListNode));
	list->value = rand()%100;
	for(index = 1; index <= 24; index++){
		nodePointer newNode = malloc(sizeof(ListNode));
		newNode->value = rand()%100;
		newNode->nextNode = NULL;
		insertSort(list,newNode);
	}
	printList(list);
	int sum = 0;
	nodePointer currentNode = list;
	while(currentNode != NULL){
		sum += currentNode->value;
		currentNode = currentNode->nextNode;
	}
	printf("\nThe sum of the list's elements is %d", sum);
	printf("\nThe avarage of the list's elements is %f\n", ((float) sum / 25));

}

/*
 *This function create a list and after invert it on a another one
 * */
void invertList()
{
	/*Creating the first list*/
	nodePointer list = createRandomList(10);
	printf("\nThe origin list is: ");
	printList(list);
	/*Creating a new list inverting the first one*/
	nodePointer invertedList = NULL;
	nodePointer currentNode = list;
	while(currentNode != NULL){
		nodePointer tempNode = currentNode->nextNode;
		currentNode->nextNode = NULL;
		currentNode->nextNode = invertedList;
		invertedList = currentNode;
		currentNode = tempNode;
		
	}
	printf("\nThe inverted list is: ");
	printList(invertedList);
	
	
}

/*
 *This function creat a list with random values between 0 and 100;
 * The list's length is passed on the parameter
 * */
nodePointer createRandomList( int lenght)
{
	nodePointer list = NULL;
	int index;
	srand(time(NULL));
	list = malloc(sizeof(ListNode));
	list->value = rand()%100;
	for(index = 1; index < lenght; index++){
		nodePointer newNode = malloc(sizeof(ListNode));
		newNode->value = rand()%100;
		newNode->nextNode = NULL;
		insertList(list,newNode);
	}
	return list;
}

/*
 *This function insert a element on the end of the list
 * */
void insertList(nodePointer list, nodePointer newNode)
{
	nodePointer currentNode = list;
	if(list == NULL){ /*It's the first node. The first insert on this list*/
		list = newNode;
		return;
	}
	while(currentNode != NULL){
		if(currentNode->nextNode == NULL){
			currentNode->nextNode = newNode;
			return;
		}else{
			currentNode = currentNode->nextNode;
		}
	}
	

}

