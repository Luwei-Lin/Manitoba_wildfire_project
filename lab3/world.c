//-----------------------------------------
// NAME: Luxiang Lin
// STUDENT NUMBER: 7900607
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Mehdi Niknam
// ASSIGNMENT: 2
//
// REMARKS: Implements Conway's Game of life.
//
//-----------------------------------------
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>

#define MAX_size 60
#define MAX_LEN 80

typedef enum BOOL { false, true } boolean;
boolean isCircle();
void creatList();
//store each change
void checkWorld();
//chech world state
void creatWorld ();
// inialized 2Darray
void UpdateWorld();
//identify new generation
void loadWorld();
//print the output
const char ALIVE = '*';
const char DEAD ='.';
typedef struct SPACE
{
  int row;
  int col;
  char arr[MAX_size][MAX_size];
}Space;
 

typedef struct ListNode
{
  Space space;
  struct ListNode *next;
} ListNode, *LinkedList;

// boolean isCircle(LinkedList head) {
//   boolean b = true;
  
//   ListNode *current = head;
//   while (current->next != NULL) {
//       ListNode *previous = current;
//       current = current->next;
//       for (int i = 0; i < current->space.row; i++) {
//         for (int j = 0; j  < current->space.col; j++) {
//            if(previous->space.arr[i][j] != current->space.arr[i][j]) {
//              b = false;
//              return b;
//            }
//         }
//       }
//       
//       return b;
//   }
// }     

Space makeSpace(int row, int col, char arry[][col])
{ 
  assert( row >= 0);
  assert( row <= MAX_size);
  assert( col >= 0);
  assert( col <= MAX_size);
  Space newSpace;
  newSpace.row = row;
  newSpace.col = col;
  for(int i = 0; i < row ; i++){
    for(int j = 0; j < col ; j++){
      newSpace.arr[i][j] = arry[i][j];
    }
   
  }
  checkWorld(row, col, newSpace.arr);
  return newSpace;
}

LinkedList insertNewNode(LinkedList head, ListNode *listnode) {
  if (head == NULL) {
    head = listnode;
    return head;
  }
  ListNode *current_node = head;

  while(current_node->next != NULL) {
    current_node = current_node->next;
  }
  current_node->next = listnode;
  return head;
}

#ifndef NDEBUG
  int condition = 0;

  int main()
  {
	  creatWorld();
	  return 0;
  }
#else
  int condition = 1;

  int main()
  {
	  creatWorld();
	  return 0;
  }
}
#endif



void checkWorld(int row, int col, char world[][col])
{
  
  for (int i=0; i<row; i++)
  {
    for (int j=0; j<col; j++)
    {
      assert(world[i][j]=='+' ||world[i][j]== '|' ||
      world[i][j]== '-' || world[i][j] == ALIVE || world[i][j] == DEAD);
    }
  }

}

void UpdateWorld(int row, int col, char world[][col], int num, LinkedList head)
{ 
  assert( row >= 0);
  assert( row <= MAX_size);
  assert( col >= 0);
  assert( col <= MAX_size);
  assert( num >= 0);
  assert( num <= 250);

  int count = num ;
  count++;
  if(count == 251) return;
      
  char tempWorld[row][col];
  for(int i = 0;i < row; i++)
  {
    for(int j = 0; j < col ; j++)
	  {
	    tempWorld[i][j] = world[i][j]; 
	  } 
  }
  checkWorld(row, col, tempWorld);

  for(int i = 1 ; i < row - 1; i++)
  {
    for(int j = 1; j < col - 1; j++)
	  {  
	    int n = 0;
	    if(tempWorld[i - 1][j - 1] == ALIVE){n++;}	
  	  if(tempWorld[i - 1][j] == ALIVE){n++;}	
      if(tempWorld[i - 1][j + 1] == ALIVE){n++;}	
	    if(tempWorld[i][j - 1] == ALIVE){n++;}	
      //if(world[i][j] == ALIVE){n++;}  no need	
	    if(tempWorld[i][j + 1] == ALIVE){n++;}	
	    if(tempWorld[i + 1][j-1] == ALIVE){n++;}	
	    if(tempWorld[i + 1][j] == ALIVE){n++;}	
	    if(tempWorld[i + 1][j + 1] == ALIVE){n++;}	
	    
	   
     
	   if(tempWorld[i][j] == DEAD)
	   {
	     if(n == 3)
         {
	        world[i][j] = ALIVE;
		    }
	   }else if(tempWorld[i][j] == ALIVE)
     {
	    if(n == 0|| n == 1 || n > 3)
	  	  {
		     world[i][j] = DEAD;
		    }
	    }
	  
    }
	 
  }// big for 

  assert( row >= 0);
  assert( row <= MAX_size);
  assert( col >= 0);
  assert( col <= MAX_size);

  checkWorld(row, col, world);
  
  if(condition != 1)
  {
    printf("Generation %d :\n", count);
    for(int i = 0;i < row; i++)
    {
      for(int j = 0; j < col ; j++)
	    {
	      printf("%c",world[i][j]); 
	    } 
	   printf("\n");
    }
  }else{
    Space newSpace =makeSpace(row, col, world);
    ListNode *newNode =(ListNode *)malloc(sizeof(ListNode));
    newNode->space = newSpace;
    newNode->next = NULL;
    head = insertNewNode(head, newNode);
    
    
  }
 

  int flag = 1; // same   
  for (int i = 1; i < row - 1; i++)
  {
    for (int j = 1; j < col - 1; j++)
    {
      if(tempWorld[i][j] != world[i][j])
      {
        flag = 0;// diff
        break;
      }
    }
  }
  assert( count >= 0);
  assert( count <= 250);
  assert( flag == 0 || flag == 1);

  if(flag == 0)
  {
      UpdateWorld(row,col,world,count,head);
      
  } 
  if (condition == 1 && flag == 1) 
  {

    for (int i = count - 9; i <= count; i++) {
      printf("Generation %d:\n", i);
      int k = 0;
      ListNode *copy = head;
      while (k < i - 1) {
         copy = copy->next;
         k++;    
      }
      for(int i = 0;i < copy->space.row; i++)
      {
        for(int j = 0; j < copy->space.col; j++)
        {
          printf("%c",copy->space.arr[i][j]); 
        } 
        printf("\n");
      }
      
    }
    
  }else if(condition == 1 && count ==250 )
  {
    for (int i = count - 9; i <= count; i++) {
      printf("Generation %d:\n", i);
      int k = 0;
      ListNode *copy = head;
      while (k < i - 1) {
         copy = copy->next;
         k++;    
      }
      for(int i = 0;i < copy->space.row; i++)
      {
        for(int j = 0; j < copy->space.col; j++)
        {
          printf("%c",copy->space.arr[i][j]); 
        } 
        printf("\n");
      }
      
    }
  }
  
}
void loadWorld(int row, int col, char temp[][col])
{ 
  assert( row >= 0);
  assert( row <= MAX_size);
  assert( col >= 0);
  assert( col <= MAX_size);

  char newWorld[row + 2][col + 2];
  for(int i = 0 ; i < row + 2 ; i++)
  {
     
      for (int j = 0 ; j < col + 2 ; j++)
      {
          if(j == 0 || j == col + 1)
          {
            newWorld[i][j] = '|';
          }
          if((i == 0 && j == 0 )|| (i == 0 && j == col + 1)
              || (i == row + 1 && j == 0 )|| (i == row + 1 && j == col + 1) )
          {
            newWorld[i][j] = '+';
          }  
          if((i == 0 && j >= 1 && j < col + 1) || (i == row + 1 && j >= 1&& j < col + 1))
          {
            newWorld[i][j] = '-';
          }
          if((i > 0 && i < row + 1) && (j > 0 && j < col + 1))
          { if((i > 0 && i < row + 1) && (j > 0 && j < col + 1))
            newWorld[i][j] = temp[i][j];
          }
          if(newWorld[i][j] == 'X')
          {
            newWorld[i][j] = '*';
          }else if(newWorld[i][j]=='+')
          {
            newWorld[i][j] ='+';
          }else if(newWorld[i][j]=='-')
          {
            newWorld[i][j] ='-';
          }else if(newWorld[i][j]=='|')
          {
            newWorld[i][j] ='|';
          }else
          { 
            newWorld[i][j]='.';
          }
           
        }     
           
    }//big for end
  int x = row + 2;
  int y = col + 2;
  assert( x >= 0);
  assert( x <= MAX_size);
  assert( y >= 0);
  assert( y <= MAX_size);
  

  printf("Generation 0 : \n");
    for(int i = 0;i < x ; i++)
      {
        for(int j = 0; j < y ; j++)
	        { 
            printf("%c",newWorld[i][j]);
	        } 
	    printf("\n");
      }
  checkWorld(x, y, newWorld);
  LinkedList linkedlist = NULL;
	UpdateWorld(x, y, newWorld, 0, linkedlist);

}

void creatWorld()
{
    FILE *f = fopen("life.txt", "r");
    char input[MAX_LEN];
    int row , col;
	
if(f != NULL)
{ 
  while( fgets( input, MAX_LEN, f ) != NULL )
  { 
   
    if(input[0] == '*')
    {
      fputs(input,stdout);
      fscanf(f,"%d %d",&row,&col);
      assert( row >= 0);
      assert( row <= MAX_size);
      assert( col >= 0);
      assert( col <= MAX_size);
      char temp[row][col];
      for(int i = 0; i < row; i++ )
      {
        fgets(input, MAX_LEN, f);
        strcpy(temp[i], input); 
      }
      assert(strlen(input) <= MAX_LEN);
      assert( row >= 0);
      assert( row <= MAX_LEN);
      assert( col >= 0);
      assert( col <= MAX_LEN);
      loadWorld(row, col, temp);
      
    }
   
  }
  
}
    else
    {
      printf("Error when opening a file");
      exit(1);
    }
    fclose(f);
    
    
}
