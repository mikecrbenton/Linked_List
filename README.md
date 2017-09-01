# Linked_List
CSC 250 // C Program using basic domino game to demonstrate Linked Lists &amp; Pointers

## Assignment Overview:
Program consists of 2 assignments

### Assignment 1: Structures
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

## Assignment 2:
