//CSC250 Homework 4, Mike Benton

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <time.h>   // REQUIRED CODE FOR ASSIGNMENT

// CORNER CASES INDEX  
/* 
1)ADD
- IF LINKED LIST IS NULL (NOTHING IN LIST)     			 IN MAIN & FUNCTION, LINE 83
- IF LINKED LIST NOT NULL (DOMINOS IN LIST)    			 IN MAIN & FUNCTION, LINE 88

2)DELETE
- INDEX (0) 1 DOMINO IN LIST                    		 IN MAIN ONLY, LINE 112
- INDEX (0) DOMINO(S) IN LIST               			 IN MAIN ONLY, LINE 120
- INDEX (1+) AND END OF LIST                			 IN MAIN & FUNCTION, LINE 129 & 404
- INDEX (1+) AND MIDDLE OF LIST             			 IN MAIN & FUNCTION, LINE 129 & 397

4) PLAY
- 1 DOMINO IN HEAD, NULL IN HEAD2 index(0) 		         IN MAIN ONLY, LINE 164
- 1 DOMINO IN HEAD, DOMINO(S) IN HEAD2  index(0)         	 IN MAIN ONLY, LINE 175
- DOMINOS IN HEAD, NULL IN HEAD2        index(0)         	 IN MAIN & FUNCTION, LINE 188
- DOMINOS IN HEAD, DOMINOS IN HEAD2     index(0)         	 IN MAIN & FUNCTION, LINE 202
- DOMINO(S) IN HEAD, NO DOMINOS IN HEAD2 index(1+)       	 IN MAIN & FUNCTION, LINE 223 & 511
- DOMINO(S) IN HEAD, DOMINO(S) IN HEAD2  index(1+)       	 IN MAIN & FUNCTION, LINE 236 & 511
*/

//----------------------------
typedef struct linkedList{    //DECLARING A TYPE- A NEW STRUCT TYPE

	int *number1;  // REMEMBER THESE ARE POINTERS!!
	int *number2;  // REMEMBER THESE ARE POINTERS!!
	struct linkedList *next;
} linkedList;
//----------------------------

linkedList* addDomino();  
void dominoSort(linkedList *head, linkedList *temp);
void printCurrentHand(linkedList *head);
void printPlayedHand(linkedList *head2);
void deleteDomino(linkedList *head, int index);
linkedList* playDomino(linkedList *head, int index); // FOR INDEX (1+)
linkedList* dominoPlay(linkedList *head, int index); // FOR INDEX (0)
int genRandomNumber();        // REQUIRED CODE FOR ASSIGNMENT
int useRandom = 16;           // REQUIRED CODE FOR ASSIGNMENT

//-----------------------------------------------------------MAIN
int main(int argc, char ** argv)
{
	useRandom = argc;		  // REQUIRED CODE FOR ASSIGNMENT
	srand(time(NULL));	          // REQUIRED CODE FOR ASSIGNMENT
	
	int choice = 1;			  // INITIALIZED TO 1 TO ENTER WHILE LOOP
	int index; 		          // FOR DELETE FUNCTION
	int i; 				  // COUNTER
	
	linkedList *head; 		  // DO NOT NEED MALLOC- INITIALIZED BY FUNCTION
	linkedList *tail;
	linkedList *temp;
	
	linkedList *head2=NULL;	           // WAS A SEG FAULT WHEN NOT NULLED
	linkedList *tail2=NULL;
	linkedList *temp2=NULL;
	
	while(choice != 0)
	{
	
	printf("0 to quit\n1 to add\n2 to delete\n3 to print\n4 to play\n:");
	scanf("%d", &choice);
	
		/*************************SWITCH**************************/
		switch(choice)
		{
			case(0):  
				printf("Thanks for quitting\n");
			break;
			
			case(1): //ADD
				
				if(head == NULL)         //IF THIS IS THE FIRST NODE
				{
					head = addDomino();  //HEAD WAS DECLARED EARLIER
					tail=head;
				}
				else if (head != NULL)   // ADDED "IF" ON 4-5-14 TO FIX BUG
				{
					temp = addDomino();
					
					if(*temp->number1 < *head->number1 || *temp->number1 == *head->number1)
					{
						temp->next = head;
						head = temp;    
					}	
					else // if (*temp->number1 > *head->number1)
					{	
						dominoSort(head, temp);
					}	
				} // END ELSE-IF CASE 1
				
			break;
			
			case(2): //DELETE
			
				printf("Enter the index to delete\n:");
				scanf("%d", &index);
				
				if(index == 0) 
				{
					if (head->next == NULL)  // ONLY 1 DOMINO
					{
						free(head->number1); // HEAD IS DELETED
						free(head->number2);
						free(head);
						head= NULL;          // HEAD IS RE-INITIALIZED
						tail= NULL;          // TAIL IS RE-INITIALIZED
					}
					else if (head->next !=NULL)       // INDEX 0 WITH MORE THAN ONE DOMINO
					{
						linkedList *tempNode = head;  // TEMPORARILY POINTS TO HEAD
						head = head->next;            // HEAD POINTS TO THE NEXT ONE IN LINE
						free(tempNode->number1);      // FORMERLY HEAD, IS DELETED
						free(tempNode->number2);
						free(tempNode);
					}
				}
				else //INDEX IS NOT O
				{
					 deleteDomino(head, index);       //DELETE FUNCTION
					 
					 linkedList *current=head;        //TEMPORARY VARIABLE FOR LOOP
					 
						while (current->next != NULL) //LOOP TO FIND TAIL OF THE LIST
						{
							current=current->next;	 
						}
						tail=current; 
				}
			break; //CASE 2
			
			case(3): //PRINT
			
				printCurrentHand(head); // FIRST LINKED LIST
				printPlayedHand(head2); // SECOND LINKED LIST
			
			break;
			
			case(4): //PLAY
			
				printf("Enter the index to play\n:");
				scanf("%d", &index);
				
				if(index == 0) //DELETE THE FIRST DOMINO FROM HEAD 1
				{
					
					if(head == NULL)                         // NOTHING TO DELETE
					{
						//DO NOTHING
					}
					else if(head->next == NULL)              // ONLY ONE DOMINO IN HEAD 1
					{
						if(head2 == NULL)                    // NO DOMINOS IN HEAD2
						{
							head2 = dominoPlay(head, index); 
							tail2=head2;
							
							free(head->number1);             // HEAD IS DELETED
							free(head->number2);
							free(head);
							head= NULL;          
							tail= NULL;     	
						}
						else if(head2 != NULL)               // DOMINOS IN HEAD 2
						{
							temp2 = dominoPlay(head, index);
							tail2->next = temp2; 
							tail2 = temp2;
							
							free(head->number1); 
							free(head->number2);
							free(head);
							head= NULL;          
							tail= NULL; 
						} 	
					}
					else if (head->next != NULL)              // MORE THAN 1 DOMINO IN HEAD
					{
						if (head2 == NULL)                    // NO DOMINOS IN HEAD2 
						{
						
							head2 = dominoPlay(head, index); 
							tail2=head2;
							
							linkedList *tempNode = head; 
							head = head->next;          
							free(tempNode->number1);     
							free(tempNode->number2);
							free(tempNode);		
						}
						else if (head2 != NULL) // DOMINOS IN HEAD 2
						{
							temp2 = dominoPlay(head, index);
							tail2->next = temp2; 
							tail2 = temp2;
							
							linkedList *tempNode = head; 
							head = head->next;          
							free(tempNode->number1);     
							free(tempNode->number2);
							free(tempNode);	
						}		
					}
				}// END OF IF INDEX=0
				else if (index != 0)                           //INDEX IS NOT O
				{
					 
					 if(head == NULL)                          // NOTHING IN HEAD 1
					 {
						// DO NOTHING
					 }
					 else if(head2 == NULL)                    // NO NODES IN LIST 2
					 {
						head2=playDomino(head, index);         // HEAD 2 LIST NEW NODE
						tail2=head2;                           // TAIL IS POINTING TO THE FIRST NODE
						
							linkedList *tailCounter=head;      //TEMPORARY VARIABLE FOR LOOP
						 
							while (tailCounter->next != NULL)  //LOOP TO FIND TAIL OF THE LIST 1
							{
								tailCounter=tailCounter->next;	 
							}
							tail=tailCounter;
					}
					 else if (head2 != NULL)                   // THERE ARE NODES IN LIST 2
					{
						temp2=playDomino(head, index);
						
						tail2->next = temp2; 
						tail2 = temp2;
						
							linkedList *tailCounter2=head;     //TEMPORARY VARIABLE FOR LOOP
							
							while (tailCounter2->next != NULL) //LOOP TO FIND TAIL OF THE LIST 1
							{
								tailCounter2=tailCounter2->next;	 
							}
							tail=tailCounter2;	
					}
				}
			break; //END CASE 4
			
		}// END OF SWITCH  
		
	} // END WHILE INDEX NOT(0)


} // END OF MAIN

//********************FUNCTIONS************************

int genRandomNumber()
{
	int random;
	if(useRandom == 1)
	{
		random = rand() % 13;
	}
	else
	{
		scanf("%d", &random);
	}
	return random;

} //END OF genRandomNumber FUNCTION   
//-----------------------------------------------------

linkedList* addDomino() 
{
	linkedList *newNode = malloc(sizeof(linkedList)); //CREATE NEW STRUCT
	newNode->number1 = malloc(sizeof(int));           //CREATE INT
	newNode->number2 = malloc(sizeof(int));           //CREATE INT
	newNode->next = NULL;				  //NEXT POINTER NULL
	
	printf("Enter the first number\n:");
	  //scanf("%d", newNode->number1 );
	
	*newNode->number1 = genRandomNumber();			
	
	printf("Enter the second number\n:");
	  //scanf("%d", newNode->number2 );
	
	*newNode->number2 = genRandomNumber();

	return newNode;
	
} // END OF addDomino FUNCTION
//------------------------------------------------

void printCurrentHand(linkedList *head) 
{
	
	if(head==NULL)//(head->number1 != 0 && head->number2 != 0)
	{
		printf("Current Hand:\n");
	}
	
	else
	{
		printf("Current Hand:");
		while(head != NULL)
		{
			printf("Domino (%d,%d)", *head->number1, *head->number2);
			head = head->next;
			
				if(head != NULL)
				{
					printf("...");
				}
				else 
				{
					printf("\n");
				}
		}
	}
	
} //END OF printCurrentHand FUNCTION
//-----------------------------------------------

void printPlayedHand(linkedList *head2) 
{
	
	if(head2!=NULL)//(head->number1 != 0 && head->number2 != 0)
	{
		printf("Played      :");
		while(head2 != NULL)
		{
			printf("Domino (%d,%d)", *head2->number1, *head2->number2);
			head2 = head2->next;
			
				if(head2 != NULL)
				{
					printf("...");
				}
				else 
				{
					printf("\n");
				}
		}
	}
	else if (head2==NULL)
	{
	printf("Played      :\n");
	}
	
} //END OF printPlayedHand FUNCTION
//-----------------------------------------------------

void dominoSort(linkedList *head, linkedList *temp) 
{
	
	if (head->next != NULL) 
	{
  
		if (*temp->number1 < *head->next->number1 || *temp->number1 == *head->next->number1)
		{
			temp->next = head->next;
			head->next=temp;
		}
		else 
		{
			dominoSort(head->next, temp);		
		}  
	}  
	else if (head->next == NULL)
	{
		head->next=temp;
	}  
	
} // END OF dominoSort FUNCTION

//---------------------------------------------------

void deleteDomino(linkedList *head, int index) 
{
		if(head == NULL)
		{	
		// DO NOTHING
		}
		
		else if(index ==1)
		{
			
				linkedList *nextNode = head->next;
				
				if (nextNode->next != NULL) //NOT THE END OF THE LIST
				{
					head->next = nextNode->next; //HEAD JUMPS OVER NEXTNODE
					free(nextNode->number1);
					free(nextNode->number2);
					free(nextNode);
				}
				else if (nextNode->next == NULL) // END OF THE LIST
				{
					
					free(nextNode->number1);
					free(nextNode->number2);
					free(nextNode);
					head->next = NULL;
				}
					
		}
		else
		{
			head = head->next;
			index --;
			deleteDomino(head, index);
		}
	
}
//----------------------------------------------------

linkedList* dominoPlay(linkedList *head,int index)//INDEX 0 PLAY FUNCTION
{
	// 1) CREATE A NODE
	
	linkedList *newNode = malloc(sizeof(linkedList)); //CREATE STRUCT
	newNode->number1 = malloc(sizeof(int));           //CREATE INT
	newNode->number2 = malloc(sizeof(int));           //CREATE INT
	newNode->next = NULL;				  //NEXT POINTER NULL
	
	if (head == NULL) //IS THIS NEEDED? IN MAIN?
	{
		// DO NOTHING
	}
	
	else if (index == 0)
	{
		*newNode->number1 = *head->number1;
		*newNode->number2 = *head->number2;
		
		return newNode;
	}
	else if (index == 1)
	{
		*newNode->number1 = *head->next->number1;
		*newNode->number2 = *head->next->number2;
		
		return newNode;
	}
	else
	{
		head = head->next;
		index --;
		dominoPlay(head, index);
	}
	
} // END DOMINOPLAY FUNCTION
//------------------------------------------------------

linkedList* playDomino(linkedList *head, int index)//INDEX 1 PLAY FUNCTION
{
	//TEMP VARIABLE TO STORE & RETURN NEW NODE
	
	linkedList *currentPlayed = malloc(sizeof(linkedList)); 
	currentPlayed->number1 = malloc(sizeof(int));           
	currentPlayed->number2 = malloc(sizeof(int));        
	currentPlayed->next = NULL;
	
	if(head == NULL)
	{	
		// DO NOTHING  
	}
	else
	{
		
		if(index == 0)
		{
		
				linkedList *tempNode = head;
				
				if (tempNode->next != NULL) //MORE THAN ONE DOMINO
				{
					  
					*currentPlayed->number1 = *tempNode->number1; // COPY THE INFO FROM NEW NODE
					*currentPlayed->number2 = *tempNode->number2; // YOU DON'T NEED TO POINT CURRENT TO NEW NODE TO COPY THE INFO
					 currentPlayed->next = NULL;
					
					head = tempNode->next; 
					free(tempNode->number1);
					free(tempNode->number2);
					free(tempNode);
										
					return currentPlayed; 
				}
				else if (tempNode->next == NULL) //ONLY ONE DOMINO
				{
					*currentPlayed->number1 = *tempNode->number1;
					*currentPlayed->number2 = *tempNode->number2;
					 currentPlayed->next = NULL;
					
					free(tempNode->number1);
					free(tempNode->number2);
					free(tempNode);
					
					return currentPlayed;
				}
		}
		
		else if(index ==1) //SAME CODE AS DELETE, WITH CURRENT VARIABLE TO STORE
		{
				
				linkedList *newNode = head->next;  // TEMP VARIABLE TO DELETE
				
				if (newNode->next != NULL)//NOT THE END OF THE LIST
				{
					*currentPlayed->number1 = *newNode->number1; // INSTEAD COPY THE INFO FROM NEW NODE
					*currentPlayed->number2 = *newNode->number2; // YOU DON'T NEED TO POINT CURRENT TO NEW NODE TO COPY THE INFO
					 currentPlayed->next = NULL;
					
					//REMEMBER - DELETING NEW NODE DELETES CURRENT	

					head->next = newNode->next; //HEAD JUMPS OVER NEXTNODE
					free(newNode->number1);
					free(newNode->number2);
					free(newNode);
										
					return currentPlayed; 
				}
				else if (newNode->next == NULL) //END OF THE LIST
				{
					*currentPlayed->number1 = *newNode->number1;
					*currentPlayed->number2 = *newNode->number2;
					 currentPlayed->next = NULL;
					
					//REMEMBER - DELETING NEW NODE DELETES CURRENT	

					free(newNode->number1);
					free(newNode->number2);
					free(newNode);
					head->next = NULL; //HEAD IS THE END OF THE LIST
										
					return currentPlayed;
				}
		}
		else
		{
			head = head->next;
			index --;
			playDomino(head, index);
		}
	}	
} // END OF playDomino FUNCTION
























