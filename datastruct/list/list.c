/*
 * This program manipulate a linked list
 * */
#include<stdio.h>
#include<stdlib.h>

/*This struct represents a node in our linkedlist.
 * It'll can store any type of data.
 * */
struct node{
	char data; /*node data*/
	struct node *nextNode; /*next node in the linked list*/
};

typedef struct node ListNode; /*"creating" a new type*/
typedef ListNode *ListNodePtr; /*The ListNodePtr is a pointer for a ListNode type*/

void insert(ListNodePtr *startNode, char value); /*insert a element on our list*/
char delete (ListNodePtr *startNode, char value); /*delete a element on our list*/
int isEmpty(ListNodePtr startNode); /*verefy if the list is empty*/
void printList(ListNodePtr currentPrt); /*print a list elements*/
void instructions(void); /*show the menu for user*/

int main(void){

	ListNodePtr startPtr = NULL; /*our list is empty*/
	int choice; /*user choice*/
	char  item; /*value informed by user*/

	instructions(); /*show the menu*/
	printf("?");
	scanf("%d", &choice); /*capture the user choice*/

	/*while user doesn't select third option, continue*/
	while(choice != 3){
		switch(choice){
			case 1: /*insert choice*/
				printf("Report a value: ");
				scanf("\n%c",&item);
				insert(&startPtr, item); /*insert the element on our list*/
				printList(startPtr);
				break;
			case 2: /*delete choice*/
				if(!isEmpty(startPtr)){ /*if the list is not empty, delete the element*/
					printf("Report a character that you want delete: ");
					scanf("\n%c",&item);
					if(delete(&startPtr,item)){
						printf("%c deleted.\n",item);
						printList(startPtr);
					}else{
						printf("%c not found.\n\n",item);
					}/*end else*/
				}/*end if*/
				else{
					printf("The list is empty");
				}/*end else*/
				break;
			default:
				printf("Invalid choice!\n\n");
				instructions();
				break;
		}/*end switch*/
		printf("? ");
		scanf("%d", &choice);
	}/*end while*/
	printf("Closing the program");
	return 0;
}/*end of main*/

/*Show the instructions for user*/
void instructions(void){
	printf("Report your choice:\n"
		"1 for insert an element on the list.\n"
		"2 for delete an element from the list.\n"
		"3 for close the program.\n");

}/*end instructions fuction*/

/*This fuction insert a element on the list*/
void insert(ListNodePtr *sPtr, char value){
	ListNodePtr newPtr; /*pointer for a new node*/
	ListNodePtr previusPtr; /*pointer to a previus node on the list*/
	ListNodePtr currentPtr; /*pointer to a current node on the list*/

	newPtr = malloc(sizeof(ListNode)); /*create a node*/
	
	if(newPtr != NULL){ /**/
		newPtr->data = value; /*assign a value for the node*/
		newPtr->nextNode = NULL; /*the node does't linked with any node*/
	
		previusPtr = NULL;
		currentPtr = *sPtr;

		while(currentPtr != NULL && value > currentPtr->data){
			previusPtr = currentPtr;
			currentPtr = currentPtr->nextNode;
		}/*end while*/

		if(previusPtr == NULL){
			newPtr->nextNode = *sPtr;
			*sPtr = newPtr;
		}/*end if*/
		else{
			previusPtr->nextNode = newPtr;
			newPtr->nextNode = currentPtr;
		}/*end else*/
	}/*end if*/
	else{
		printf("%c não inserido. Sem memória disponível.\n");
	}/*end else*/
}/*end insert function*/

/*This function delete a element of the list*/
char delete(ListNodePtr *sPtr, char value){
	ListNodePtr previousPtr; /*pointer to previus node on the list*/
	ListNodePtr currentPtr; /*pointer to current node on the list*/
	ListNodePtr tempPtr; /*temporary pointer to a node*/

	/*delete first node*/
	if(value == ( *sPtr )->data){
		tempPtr = *sPtr; /*point to node that is beeing remove*/
		*sPtr = ( *sPtr )->nextNode; 
		free( tempPtr );
		return value;
	}/*end if*/
	else{
		previousPtr = *sPtr;
		currentPtr = ( *sPtr )->nextNode;
		/*loop for find the correct node*/
		while(currentPtr != NULL && currentPtr->data != value){
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextNode;
		}/*end while*/
		
		if(currentPtr != NULL){
			tempPtr = currentPtr;
			previousPtr->nextNode = currentPtr->nextNode;
			free(tempPtr);
			return value;
		}/*end if*/
	}/*end else*/

	return '\0';
}/*end delete function*/

int isEmpty(ListNodePtr sPtr){
	return sPtr == NULL;
}/*end isEmpty function*/

void printList( ListNodePtr currentPtr){
	if(currentPtr == NULL){
		printf("The list is empty.\n\n");
	}/*end if*/
	else{
		printf("The list's values are: ");

		while(currentPtr != NULL){
			printf("%c --> ",currentPtr->data);
			currentPtr = currentPtr->nextNode;
		}/*end while*/
		printf("NULL\n\n");
	}/*end else*/
}/*end printList function*/
