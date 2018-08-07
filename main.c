#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {FALSE = 0, TRUE = 1, NO = 0, YES = 1} boolean;

typedef struct Node{
    char groupName[30];
    int groupSize;
    boolean groupStatus;
    struct Node *pNext;
}node;

/* forward definition of functions */
void clearToEoln();

/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v,
 *      form feed \f, and carriage return \r
 */

boolean doesNameExist(node *pHead, char name[]){
    
    while(pHead != NULL){
        
        if(strcmp(pHead->groupName, name) == 0){
            return TRUE;
        }
        
        pHead = pHead->pNext;
    }
    return FALSE;
}//End of doesNameExist

boolean updateStatus(node *pHead, char name[]){
    while(pHead != NULL){
        if(doesNameExist(pHead, name)){
            pHead->groupStatus = TRUE;
            return TRUE;
        }
        pHead = pHead->pNext;
    }
    return FALSE;
}//End of updateStatus

char *retrieveAndRemove(node **pHead, int size){
   node *temp = *pHead;
   node *curr = temp;
   node *curr2 = temp;
   char *name;
    
   //If the first node has the right group size
    if(temp != NULL && temp->groupSize <= size){
        name = temp->groupName;
        *pHead = temp->pNext;
        free(temp);
        return name;
    }
    
    //Traversing the list until the correct group size is found
    while(temp->pNext != NULL){
       
        if(temp->pNext->groupSize == size){
            curr = temp->pNext;
            curr2 = curr->pNext;
            name = curr->groupName;
            free(curr);
            temp->pNext = curr2;
            return name;
        }
        temp = temp->pNext;
    }
    return NULL;
}//End of retrieveAndRemove

int countGroupsAhead(node *pHead, char name[]){
    int groupsAhead = 0;
    
    while(pHead != NULL){
        if(strcmp(pHead->groupName, name)==0){
            return groupsAhead;
        }
        
        pHead = pHead->pNext;
        groupsAhead = groupsAhead +1;
    }
    return 0;
}//End of countGroupsAhead

void displayGroupSizeAhead(node *pHead, char name[]){
    node *temp = pHead;
    int i = 1;
    
    if(temp == NULL){
        printf("Error. List is empty.");
    }
    
    while(temp->pNext != NULL){
        if(temp->pNext->groupName == name){
            break;
        }
        printf("Group in position %d in front of this group has size. %d\n", i, temp->groupSize);
        i++;
        temp = temp->pNext;
    }
    
}//End of displayGroupSizeAhead

void displayListInformation(node* pHead){
    int groupNumber = 1;
    
    while(pHead != NULL){
        //Printing results
        printf("GROUP %d DETAILS.\n", groupNumber);
        printf("Group Name: %s\n", pHead->groupName);
        printf("Group Size: %d\n", pHead->groupSize);
        
        if(pHead->groupStatus == TRUE){
            printf("In restaurant: YES\n\n");
        }
        else{
            printf("In restaurant: NO\n\n");
        }

        groupNumber = groupNumber + 1;
        pHead = pHead->pNext;
    }
    
}//End of displayListInformation

void addToList(node **pHead, char name[], int size, boolean group){
    int i;
    node* current = *pHead;
    node* previous = NULL;
    node *temp = (node*)malloc(sizeof(node));
    
    while(current != NULL){
        previous = current;
        current = current->pNext;
    }
    
    //Copying group name from user input
    for(i = 0; i<30; i++){
        temp->groupName[i] = name[i];
    }
    temp->groupSize = size;
    temp->groupStatus = group;
    temp->pNext = current;
    
    if(previous == NULL){
        *pHead = temp;
    }
    else{
        previous->pNext = temp;
    }
    
}//End of addToList


int getNextNWSChar ()
{
    int ch;
    
    ch = getc(stdin);
    if (ch == EOF)
        return ch;
    while (isspace (ch))
    {
        ch = getc(stdin);
        if (ch == EOF)
            return ch;
    }
    return ch;
}

/* read in the next Positive Integer or error:    */
/* This is based on the Mathematical definition of a Postive Integer */
/*    zero is not counted as a positive number */
int getPosInt ()
{
    int value = 0;
    
    /* clear white space characters */
    int ch;
    ch = getc(stdin);
    while (!isdigit(ch))
    {
        if ('\n' == ch)  /* error \n ==> no integer given */
            return 0;
        if (!isspace(ch)) /* error non white space ==> integer not given next */
        {
            clearToEoln();
            return 0;
        }
        ch = getc(stdin);
    }
    
    value = ch - '0';
    ch = getc(stdin);
    while (isdigit(ch))
    {
        value = value * 10 + ch - '0';
        ch = getc(stdin);
    }
    
    ungetc (ch, stdin);  /* put the last read character back in input stream */
    
    /* Integer value of 0 is an error in this program */
    if (0 == value)
        clearToEoln();
    
    return value;
}

/* read in the name until the end of the input */
char *getName()
{
    /* skip over the white space characters */
    int ch;
    ch = getc(stdin);
    while (isspace(ch))
    {
        if ('\n' == ch)  /* error \n ==> no integer given */
            return NULL;
        ch = getc(stdin);
    }
    
    char *word;
    int size;
    size = 10;
    word = (char *) malloc (sizeof(char) * size);
    
    // read in character-by-character until the newline is encountered
    int count = 0;
    
    while (ch != '\n')
    {
        if (count+1 >= size)
        {
            // to grow an array to make it "dynamically sized" using malloc
            char* temp;
            int i;
            size = size * 2;
            temp = (char *) malloc (sizeof(char) * size);
            
            // printf ("Growing array from size %d to size %d\n", count, size);
            // copy the characters to the new array
            for (i = 0 ; i < count ; i++)
                temp[i] = word[i];
            
            free (word);
            word = temp;
        }
        
        word[count] = ch;
        count++;
        word[count] = '\0';
        
        // read next character
        ch = getc(stdin);
    }
    
    if (count > 30)
    {
        count = 30;
        word[count] = '\0';
    }
    
    /* clear ending white space characters */
    while (isspace (word[count-1]))
    {
        count--;
        word[count] = '\0';
    }
    
    return word;
}

/* Clear input until next End of Line Character - \n */
void clearToEoln()
{
    int ch;
    
    do {
        ch = getc(stdin);
    }
    while ((ch != '\n') && (ch != EOF));
}

/* Print out a list of the commands for this program */
void printCommands()
{
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("a <size> <name> - to add a group to the wait list\n");
    printf ("c <size> <name> - to add a call-ahead group to the wait list\n");
    printf ("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
    printf ("r <table-size> - to retrieve the first waiting group that can fit at the available table size\n");
    printf ("l <name> - list how many groups are ahead of the named group\n");
    printf ("d - display the wait list information\n");
    
    /* clear input to End of Line */
    clearToEoln();
}

void doAdd (node **pHead)
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Add command requires an integer value of at least 1\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Add command requires a name to be given\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    //Checking if name already exists in queue. Give error if it does
    if(doesNameExist(*pHead, name)){
        printf("Name already exists in queue, no need to add it again.\n");
    }
    else{
        printf ("Adding group \"%s\" of size %d\n", name, size);
        
        // add code to perform this operation here
        addToList(pHead, name, size, TRUE);
    }
}//End of doAdd


void doCallAhead (node **pHead)
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 1\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Call-ahead command requires a name to be given\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    //Checking if name already exists in queue. Give error if it does
    if(doesNameExist(*pHead, name)){
        printf("Name already exists in queue, no need to add it again.\n");
    }
    else{
        printf ("Call-ahead group \"%s\" of size %d\n", name, size);
        
        // add code to perform this operation here
        addToList(pHead, name, size, FALSE);
    }
    
}//End of doCallAhead

void doWaiting (node **pHead)
{
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Waiting command requires a name to be given\n");
        printf ("Waiting command is of form: w <name>\n");
        printf ("  where: <name> is the name of the group that is now waiting\n");
        return;
    }
    
    //Checking if name exists and give an error if it does not
    if(!doesNameExist(*pHead, name)){
        printf("Name is not on the waiting list, tell the customer that they are lying");
    }
    else{
    printf ("Waiting group \"%s\" is now in the restaurant\n", name);
    
    // add code to perform this operation here
        updateStatus(*pHead, name);
    }
    
}//End of doWaiting

void doRetrieve (node **pHead)
{
    /* get table size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Retrieve command requires an integer value of at least 1\n");
        printf ("Retrieve command is of form: r <size>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        return;
    }
    clearToEoln();
    //printf ("Retrieve (and remove) the first group that can fit at a table of size %d\n", size);
    
    char *name = retrieveAndRemove(pHead, size);
    printf("The group with the name: %s has been removed from the waiting list.\n", name);
    
}//End of doRetrieve

void doList (node **pHead)
{
    int numGroups;
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: l <name>\n");
        printf ("  where: <name> is the name of the group to inquire about\n");
        return;
    }
    
    //Checking if name exists
    if(!doesNameExist(*pHead, name)){
        printf("This group not in line to be seated.\n");
    }
    else{
        numGroups =  countGroupsAhead(*pHead, name);
        printf ("Group \"%s\" is behind the following number of groups: %d\n", name, numGroups);
        displayGroupSizeAhead(*pHead, name);
    }
    
}//End of doList

void doDisplay (node **pHead)
{
    clearToEoln();
    printf ("Display information about all groups.\n\n");
    
    // add code to perform this operation here
    displayListInformation(*pHead);
    
}//End of doDisplay

int main (int argc, char **argv)
{
    int ch;
    node *pHead = NULL;
        
    printf ("Starting Restaurant Wait List Program...\n\n");
    printf("To list all available commands type: ?\n");
    printf ("Enter command: ");
    
    while ((ch = getNextNWSChar ()) != EOF)
    {
        /* check for the various commands */
        if (ch == 'q')
        {
            printf ("Quitting Program\n");
            return (0);
        }
        else if (ch == '?')
        {
            printCommands();
        }
        else if(ch == 'a')
        {
            doAdd(&pHead);
        } 
        else if(ch == 'c')
        {
            doCallAhead(&pHead);
        } 
        else if(ch == 'w')
        {
            doWaiting(&pHead);
        } 
        else if(ch == 'r')
        {
            doRetrieve(&pHead);
        } 
        else if(ch == 'l')
        {
            doList(&pHead);
        } 
        else if(ch == 'd')
        {
            doDisplay(&pHead);
        } 
        else
        {
            printf ("%c - in not a valid command\n", ch);
            printf ("For a list of valid commands, type ?\n");
            clearToEoln();
        }
        
        printf ("\nEnter command: ");
    }//End of while loop
    
    printf ("Quiting Program - EOF reached\n");
    return 1;
}//End of main
