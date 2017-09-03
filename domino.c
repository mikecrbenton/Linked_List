//CSC250 Homework 4, Mike Benton

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <time.h>   // REQUIRED CODE FOR ASSIGNMENT

// CORNER CASES INDEX  
/* 
1)ADD
- IF LINKED LIST IS NULL (NOTHING IN LIST)     			      IN MAIN & FUNCTION, LINE 85
- IF LINKED LIST NOT NULL (DOMINOS IN LIST)    			      IN MAIN & FUNCTION, LINE 90
2)DELETE
- INDEX ENTERED IS (0) - THERE IS 1 DOMINO IN LIST                    IN MAIN ONLY, LINE 132
- INDEX ENTERED IS (0) - THERE IS MORE THAN 1 DOMINO(S) IN LIST       IN MAIN ONLY, LINE 142
- INDEX (ABOVE 0) AND IT IS THE END OF LIST                           IN MAIN & FUNCTION, LINE 153 & 468
- INDEX (ABOVE 0) AND IT IS IN MIDDLE OF LIST             	      IN MAIN & FUNCTION, LINE 153 & 491
4) PLAY
- 1 DOMINO IN LIST 1, NULL IN LIST 2                  index(0)        IN MAIN ONLY, LINE 211
- 1 DOMINO IN LIST 1, THERE ARE DOMINO(S) IN LIST 2   index(0)        IN MAIN ONLY, LINE 224
- DOMINOS IN LIST 1, NULL IN LIST 2                   index(0)        IN MAIN & FUNCTION, LINE 241
- DOMINOS IN LIST 1, DOMINOS IN LIST 2                index(0)        IN MAIN & FUNCTION, LINE 255
- DOMINO(S) IN LIST 1, NO DOMINOS IN LIST 2           index(ABOVE 0)  IN MAIN & FUNCTION, LINE 279 & 539
- DOMINO(S) IN LIST 1, DOMINO(S) IN LIST 2            index(ABOVE 0)  IN MAIN & FUNCTION, LINE 294 & 539
*/

//----------------------------
typedef struct linkedList{       //DECLARING A TYPE- A NEW STRUCT TYPE

	int *number1;            // REMEMBER THESE ARE POINTERS - HOLDS 1ST DOMINO NUMBER
	int *number2;            // REMEMBER THESE ARE POINTERS - HOLDS 2ND DOMINO NUMBER
	struct linkedList *next; //POINTER TO THE NEXT STRUCT
} linkedList;
//----------------------------

linkedList* addDomino();  			      //RETURNS A NEW DOMINO (NODE)
void dominoSort(linkedList *head, linkedList *temp);
void printCurrentHand(linkedList *head);
void printPlayedHand(linkedList *head2);
void deleteDomino(linkedList *head, int index);
linkedList* playDomino(linkedList *head, int index);  // FOR INDEX (USER INPUT ABOVE 0)
linkedList* dominoPlay(linkedList *head, int index);  // FOR INDEX (USER INPUT 0)
int genRandomNumber();                                // REQUIRED CODE FOR ASSIGNMENT
int useRandom = 16;                                   // REQUIRED CODE FOR ASSIGNMENT
int count = 0;                                        // KEEPS COUNT OF NUMBER OF DOMINOS IN LIST 1 (NOT PLAYED)
int checkUserInput(int index, int choice);            // CHECKS USER INPUT FOR DELETE AND PLAY

//-----------------------------------------------------------MAIN
int main(int argc, char ** argv)
{
	useRandom = argc;		  // REQUIRED CODE FOR ASSIGNMENT - 
	srand(time(NULL));	          // REQUIRED CODE FOR ASSIGNMENT
	
	int choice = 1;			  // INITIALIZED TO 1 TO ENTER WHILE LOOP
	int index; 		          // FOR DELETE FUNCTION
	int i; 				  // COUNTER
	
	linkedList *head; 		  // REPRESENTS THE FIRST LIST OF DOMINOS (CURRENT HAND)
	linkedList *tail;
	linkedList *temp;		  // DO NOT NEED MALLOC- INITIALIZED BY FUNCTION
	
	linkedList *head2=NULL;	          // REPRESENTS THE SECOND LIST OF DOMINOS (PLAYED HAND)
	linkedList *tail2=NULL;
	linkedList *temp2=NULL;
	
	printf("\nWELCOME TO THE DOMINO GAME\n");

	while(choice != 0)
	{
	
	printf("0 Quit The Game\n1 Add Dominos\n");
	printf("2 Delete Dominos\n3 Print Your Hand\n4 Play a Domino\n:");
	scanf("%d", &choice);
	
		/*************************SWITCH**** END / DELETE / PRINT / PLAY **********************/
		switch(choice)
		{
			case(0):  
				printf("Thanks for Playing!\n"); // END GAME
			break;
			
			case(1): //ADD
				
				if(head == NULL)         // IF THIS IS THE FIRST DOMINO (NODE)
				{
					head = addDomino();  // RETURNS A NEW DOMINO (NODE) // HEAD WAS DECLARED EARLIER IN LINE 59
					tail=head;	     // ONLY ONE DOMINO - TAIL POINTS TO HEAD OF THE LIST
				}
				else if (head != NULL)       // IF THERES MORE THAN ONE DOMINO(NODE) IN LIST  //**ADDED "IF" ON 4-5-14 TO FIX BUG
				{
					temp = addDomino();  // RETURNS A NEW DOMINO TO A TEMPORARY NODE
					
					if(*temp->number1 < *head->number1 || *temp->number1 == *head->number1) // IF NEW DOMINO IS LESS THAN OR EQUAL TO HEAD 
					{
						temp->next = head;                                              // NEW DOMINO POINTS TO HEAD
						head = temp;    													// NEW DOMINO BECOMES HEAD
					}	
					else // if (*temp->number1 > *head->number1)
					{	
						dominoSort(head, temp);												// SORT THROUGH LIST
					}	

				} // END ELSE-IF CASE 1
				
			break; 
			
			case(2): //DELETE
			
				printf("\n");

				printCurrentHand(head); // PRINT LIST 1 (CURRENT HAND) TO SHOW USER THE DOMINOS

				if(head == NULL){

					printf("\nThere is nothing to delete...\n\n");
					break;
				}

				printf("\nEnter the domino you want to delete ( 1 through %d):\n",count);
				scanf("%d", &index);

				printf("\n");
				
				index = checkUserInput(index, 1); //RETURNS A (-1) IF INCORRECT USER INPUT

				if(index == -1){                  //IF INCORRECT INPUT , BREAK AND BACK TO MENU
					break;
				}
				
				if(index == 0) // NOTE** USER INPUT WOULD HAVE BEEN 1 (NOT 0) (IT IS DECREMENTED TO O FOR CORRECT LIST COUNT)
				{
					if (head->next == NULL)      // THERE IS ONLY 1 DOMINO IN LIST
					{
						free(head->number1); // HEAD IS DELETED
						free(head->number2);
						free(head);
						head= NULL;          // HEAD IS RE-INITIALIZED
						tail= NULL;          // TAIL IS RE-INITIALIZED

						count--; // DECREMENT COUNT TO SHOW CORRECT NUMBER OF DOMINOS IN LIST 1
					}
					else if (head->next !=NULL)       // DELETE THE FIRST DOMINO BUT THE LIST HAS MORE THAN ONE DOMINO
					{
						linkedList *tempNode = head;  // TEMPORARILY POINTS TO HEAD
						head = head->next;            // HEAD POINTS TO THE NEXT ONE IN LINE
						free(tempNode->number1);      // FORMERLY HEAD, IS DELETED
						free(tempNode->number2);
						free(tempNode);

						count--; // DECREMENT COUNT TO SHOW CORRECT NUMBER OF DOMINOS IN LIST 1
					}
				}
				else // INDEX IS NOT O ( A NUMBER ABOVE THE FIRST DOMINO WAS ENTERED FROM USER INPUT )
				{	
					 	deleteDomino(head, index);       
					 
					 	linkedList *current=head;        //TEMPORARY VARIABLE FOR LOOP
					 
							while (current->next != NULL) //LOOP TO FIND TAIL OF THE LIST
							{
								current=current->next;	 
							}
							tail=current;

							count--;             // DECREMENT COUNT TO SHOW CORRECT NUMBER OF DOMINOS IN LIST 1
				}

			break; // END CASE 2 (DELETE)
			
			case(3): //PRINT
			
				printf("\n");
				printCurrentHand(head); // FIRST LINKED LIST
				printPlayedHand(head2); // SECOND LINKED LIST
				printf("\n");
			
			break;
			
			case(4): //PLAY
			
				printf("\n");

				printCurrentHand(head); // PRINT HAND TO SHOW USER THE DOMINOS

				if(head == NULL){       // IF THE LIST IS EMPTY

					printf("\nThere is nothing to play...\n\n");
					break;
				}

				printf("Enter the index to play ( 1 through %d):\n",count);
				scanf("%d", &index);

				printf("\n");
				
				index = checkUserInput(index, 2); //RETURNS -1 IF INCORRECT USER INPUT

				if(index == -1){ //IF INCORRECT USER INPUT , BREAK AND GO BACK TO MENU
					break;
				}
				
				if(index == 0) // DELETE THE FIRST DOMINO FROM LIST 1
				{
					
					if(head == NULL)                         // NOTHING TO DELETE
					{
						//DO NOTHING //**CODE ALSO ADDED TO CHECK THIS IN checkUserInput() FUNCTION
					}
					else if(head->next == NULL)              // ONLY ONE DOMINO IN LIST 1
					{
						if(head2 == NULL)                // NO DOMINOS IN LIST 2
						{
							head2 = dominoPlay(head, index); 
							tail2=head2;
							
							free(head->number1);     // HEAD IS DELETED
							free(head->number2);
							free(head);
							head= NULL;          
							tail= NULL; 

							count--; // DECREMENT COUNT TO SHOW CORRECT NUMBER OF DOMINOS    	
						}
						else if(head2 != NULL)            // THERE ARE MULTIPLE DOMINOS IN LIST 2
						{
							temp2 = dominoPlay(head, index);
							tail2->next = temp2; 
							tail2 = temp2;
							
							free(head->number1); 
							free(head->number2);
							free(head);
							head= NULL;          
							tail= NULL; 

							count--; // DECREMENT COUNT TO SHOW CORRECT NUMBER OF DOMINOS IN LIST 1  
						} 	
					}
					else if (head->next != NULL)              // THERE IS MORE THAN 1 DOMINO IN LIST 1
					{
						if (head2 == NULL)                // NO DOMINOS IN LIST 2 
						{
						
							head2 = dominoPlay(head, index); 
							tail2=head2;
							
							linkedList *tempNode = head; 
							head = head->next;          
							free(tempNode->number1);     
							free(tempNode->number2);
							free(tempNode);	

							count--; // DECREMENT COUNT TO SHOW CORRECT NUMBER OF DOMINOS IN LIST 1  	
						}
						else if (head2 != NULL) // IF THERE ARE DOMINOS IN LIST 2
						{
							temp2 = dominoPlay(head, index);
							tail2->next = temp2; 
							tail2 = temp2;
							
							linkedList *tempNode = head; 
							head = head->next;          
							free(tempNode->number1);     
							free(tempNode->number2);
							free(tempNode);	

							count--; // DECREMENT COUNT TO SHOW CORRECT NUMBER OF DOMINOS IN LIST 1  
						}		
					}
				}// END OF IF INDEX=0

				else if (index != 0) // USER INPUT WAS ABOVE THE FIRST DOMINO
				{
					 
					 if(head == NULL) // NOTHING IN LIST 1
					 {
						// DO NOTHING //CODE ALSO ADDED TO CHECK THIS IN checkUserInput() FUNCTION
					 }
					 else if(head2 == NULL)                          // NO DOMINOS IN LIST 2
					 {
						head2 = playDomino(head, index);         // HEAD2 LIST NEW NODE
						tail2 = head2;                           // TAIL IS POINTING TO THE FIRST NODE
						
							linkedList *tailCounter = head;  //TEMPORARY VARIABLE FOR LOOP
						 
							while (tailCounter->next != NULL)//LOOP TO FIND TAIL OF LIST 1
							{
								tailCounter=tailCounter->next;	 
							}
							tail=tailCounter;

							count--; // DECREMENT COUNT TO SHOW CORRECT NUMBER OF DOMINOS IN LIST 1
					}
					 else if (head2 != NULL) // THERE ARE DOMINOS IN LIST 2
					{
						temp2=playDomino(head, index);
						
						tail2->next = temp2; 
						tail2 = temp2;
						
							linkedList *tailCounter2=head;       //TEMPORARY VARIABLE FOR LOOP
							
							while (tailCounter2->next != NULL)   //LOOP TO FIND TAIL OF THE LIST 1
							{
								tailCounter2=tailCounter2->next;	 
							}
							tail=tailCounter2;	

							count--; // DECREMENT COUNT TO SHOW CORRECT NUMBER OF DOMINOS IN LIST 1
					}
				}
			break; //END CASE 4 (PLAY)
			
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
	newNode->number1 = malloc(sizeof(int));           //CREATE MEMORY FOR INT
	newNode->number2 = malloc(sizeof(int));           //CREATE MEMORY FOR INT
	newNode->next = NULL;				  //NEXT POINTER NULL
		
	//SIMULATE DRAWING RANDOM DOMINO		  
	*newNode->number1 = genRandomNumber();			
	*newNode->number2 = genRandomNumber();

	printf("\nThe domino you drew was (%d,%d)\n\n", *newNode->number1, *newNode->number2);

	count++; //INCREMENT NUMBER OF DOMINOS 

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
		printf("Current Hand:   ");
		int currentCount = 1; //VARIABLE TO SHOW INDEX OF LIST FOR PRINTOUT
		int rowCount =3;      //VARIABLE TO KEEP COUNT OF ROWS FOR PRINTOUT
		while(head != NULL)
		{
			printf("|#%d| ",currentCount); // SHOW USER THE NUMBER OF THE DOMINO IN THE LIST
			printf("Domino (%d,%d)", *head->number1, *head->number2);
			head = head->next;
			
				if(head != NULL)
				{
					if(currentCount == rowCount ){
						printf("\n");
						printf("            ");  // LINE UP NEXT ROW OF 3 DOMINOS
						rowCount = rowCount + 3; // PRINT OUT IN ROWS OF 3
					}

					printf("\t");
					currentCount++;
				}
				else 
				{
					printf("\n\n");
				}
		}
	}
	
} //END OF printCurrentHand FUNCTION
//-----------------------------------------------

void printPlayedHand(linkedList *head2) 
{
	
	if(head2!=NULL)//(head->number1 != 0 && head->number2 != 0)
	{
		printf("Played Hand :   ");
		int currentCount = 1; //VARIABLE TO SHOW INDEX OF LIST FOR PRINTOUT
		int rowCount = 3;     //VARIABLE TO KEEP COUNT OF ROWS FOR PRINTOUT
		while(head2 != NULL)
		{
			printf("|#%d| ",currentCount); // SHOW USER THE NUMBER OF THE DOMINO IN THE LIST
			printf("Domino (%d,%d)", *head2->number1, *head2->number2);
			head2 = head2->next;
			
				if(head2 != NULL)
				{
					if(currentCount == rowCount ){
						printf("\n");
						printf("            ");  // LINE UP NEXT ROW OF 3 DOMINOS
						rowCount = rowCount + 3; // PRINT OUT IN ROWS OF 3
					}
					printf("\t");
					currentCount++;
				}
				else 
				{
					printf("\n\n");
				}
		}
	}
	else if (head2==NULL)
	{
	printf("Played Hand  :\n");
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
	//TEMP VARIABLE TO STORE & RETURN NEW LINKEDLIST NODE
	
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

//--------------------------------------------------------------

int checkUserInput(int index, int choice){

	//CHECK ON USER INPUT - USER SHOULD NOT ENTER 0 OR ABOVE THE NUMBER OF DOMINOS IN HAND
		if(index == 0){

			//USER INPUT SHOULD BE 1 OR ABOVE FOR PROGRAM CODE TO CALCULATE CORRECTLY
			if(choice == 1){
				printf("\nNumber %d is not a valid domino to delete!\n\n",index);
			}
			if(choice == 2){
				printf("\nNumber %d is not a valid domino to play!\n\n",index);
			}

			return -1; // IF INCORRECT USER INPUT RETURN -1

		}else if( index <= count ){

			index--; // USER SHOULD ENTER BETWEEN 1 AND 100.  NEED TO SUBTRACT THE INDEX  
				     // BY ONE TO GET CORRECT ARRAY COUNT FROM O (NOT OFF BY ONE)

			return index; // IF CORRECT USER INPUT RETURN INDEX
					
		}else{

			//USER SHOULD NOT ENTER A NUMBER ABOVE AMOUNT OF DOMINOS - OR OTHER INPUT
			if(choice == 1){
				printf("\nNumber %d is not a valid domino to delete!\n\n",index);
			}
			if(choice == 2){
				printf("\nNumber %d is not a valid domino to play!\n\n",index);
			}

			return -1; // IF INCORRECT USER INPUT RETURN -1
		}
} // ENDOF checkUserInput FUNCTION
