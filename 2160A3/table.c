//-----------------------------------------
// NAME: Luxiang Lin
// STUDENT NUMBER: 7900607
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Mehdi Niknam
// ASSIGNMENT: 3
//
// REMARKS: Implements table.
//
//-----------------------------------------
#include"table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static void Sort();
typedef struct NODE Node;
 struct NODE{
    int number;
    struct NODE *next;
};

// typedef struct TABLE{
//     Node *head;
//     Node *trakNode;
//     int  numNodes;
//     int numTrakNode;
// }Table;

static  Node *top = NULL;
static  Node *trackNode = NULL;

static void validTable(Node *T)
{
    assert(T != NULL);
    
}

Boolean insertItem( int item )
{   
    
    if(top == NULL)
    {
        Node *new_node = (Node *)malloc(sizeof(Node)); 
        assert(new_node);
        Node *new_trackNode = (Node *)malloc(sizeof(Node));
        assert(new_trackNode); 
        new_node->number = item;
        new_node->next = NULL;
        top = new_node;
        
        new_trackNode->next = NULL;
        trackNode = new_trackNode;
        return true;
    }else if(search(item))
    {
        return false;
    }else
    {
    
    Node *newNode = (Node *)malloc(sizeof(Node));
    assert(newNode);
    newNode->number = item;
    newNode->next = top;
    top = newNode;
    Sort(top);
    validTable(top);
    return true;
   
    }
   
}

static void Sort(Node * node){
    
    Node *curr ,*prev;
    curr = node;
   

    while((curr) != NULL)
    {
        prev = curr->next;
        
        while(prev != NULL)
        {  
            if((curr-> number) > (prev->number))
          {     
                int t = curr->number;
                curr->number = prev->number; 
                prev->number = t;
          }

            prev = prev->next;
            
        }
        curr = curr->next;
      
    }
    validTable(node);
}//static sortTable()





Boolean firstItem( int * const item )
{
    Boolean result =false;
    validTable(top);
    if (top)
    {
        *item = top->number;
        trackNode = top->next;
        result = true;
    }
    return result;
}
Boolean nextItem( int * const item )
{   validTable(top);
    Boolean result = false;
    if(trackNode)
    {
        *item = trackNode->number;
        trackNode = trackNode->next;
        result = true;
    }
    return result;
}

void clearTable( )
{
    Node *curr =NULL;
    
    if(top != NULL)
    {
        curr = top;
        assert(curr);
    }
    while(top != NULL)
    {
        top = top->next;
        free(curr);
        curr = top;
    }
    assert(top == NULL);
}
Boolean removeItem( int item )
{   
    Boolean result = false;

    if (search(item)) {
        Node *curr = top;
        assert(curr);

        if (curr->number == item) {
            Node * temp;
            temp = top;
            assert(temp);
            top = curr->next;
            free(temp);
            result = true;
        } else {
            while (curr->next->number != item && curr->next != NULL) {
                curr = curr->next;
            }
            Node *nextTemp = curr->next;
            assert(nextTemp);

            curr->next = nextTemp->next;
            free(nextTemp);
            result = true;
        }
    }  
    assert(search(item) == false);
   return result;
}

Boolean search( int item )
{   
    Node *curr = top;  
    while (curr != NULL)
    {   
        if(curr->number == item ){
            return true;
        }else{ 
            curr = curr->next;
        }
    }
    
    return false;
}


