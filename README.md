# Linked_List
CSC 250 // C Program using basic domino game to demonstrate Linked Lists &amp; Pointers

## Assignment Overview:
Program consists of 2 assignments

### Assignment 1: Structures, Linked List, Pointers
This assignment will be to add and remove dominos from an array of dominos. Your structure will be a domino. 
It will hold 3 fields (used, number1 and number2).The used field will either hold Y or N. If used is a Y, 
then number 1 and number 2 are the two numbers for the domino. Your main function will only allocate the array
of dominos and read the option for which action to take. Actions are print, add, remove and quit (exits the program).
You must write at least the following four functions.
* int getIndex();
* void addDomino(Domino * d, int size);
* void removeDomino(Domino * d, int offset);
* void print(Domino * d, int size);
* The **getIndex** function will get the index to be removed.
* The **addDomino** function will find a free spot, and then read in number1 and number2 for that domino. It will also set that domino as being used (used = ‘Y’).
* The **removeDomino** function will remove the domino at the location index. This can be done by setting the used flag for that index to ’N’);
* The **print** function will print out all the used dominos (used field = Y).

### Assignment 2: Extension of Assignment 1
This assignment will be to simulate more accurately the game of Mexican Trains. We are only going to emulate a portion of the
game. For the real game, each player select 15 dominos. Then the player with the highest double plays that double in the middle. Each player then has a chance to play as many dominos in a row that they can legally play. If the middle is 4:4 then you could play a 4:1 next but not a 2:3 (the 4’s match). If you cannot play, you draw another domino from theboneyard (dominos that are right-side-down and all mixed up).
In our game we will simulate a single player drawing dominos (adding them to their hand) and then playing them. I only have one required function, which is listed below. In this game, you may play any domino as the first domino.
##### Requirements.
* I. You must use a domino structure.
* II. The two sets of dominoes must be stored in separate linked lists.
* III. The played list is always appended to the end.
* IV. When a domino is inserted in the hand, the hand is sorted by the first domino number.
* V. Dominoes may be deleted from the from your hand.
* VI. Dominoes may not be deleted from the played hand.
* VII. Deleted Dominoes must be freed using the free function.


