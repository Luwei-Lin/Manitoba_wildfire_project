//-----------------------------------------
// NAME: Luxiang Lin
// STUDENT NUMBER: 7900607
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Mehdi Niknam
// ASSIGNMENT: 3
//
// REMARKS: test table.
//
//-----------------------------------------
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "table.h"
 
#define MAX_SIZE 100
void testEmpty();
void testInsert();
void testRemove();
void testsearch();

void cleanTable();
Boolean testMatched();

typedef struct
{
  int output[MAX_SIZE];
  int size; 
} answer;


static int testsPassed;
static int testsFailed;


int main()
{
    testsPassed = 0;
    testsFailed = 0;
    printf("-----Start test-----");
    testInsert();
    testsearch();
    testRemove();
    testEmpty();
    printf("\ntestsFailed: %d\n", testsFailed);
    printf("\ntestsPassed: %d\n", testsPassed);
    printf("-----End test-----");
    return 0;
}

void testInsert()
{   

    int testarr[5] = {3,4,3,5,-3}; 
    int answer[4] = {-3,3,4,5};
    printf( "\nTesting insertItem:\n-----" );
    printf("test array: ");
    for (int i = 0; i < 5; i++)
    {
       
        printf( "%d ,", testarr[i]);
        insertItem(testarr[i]);
    }
    if(testMatched(4,answer)){
        printf("-----Inserted successfully-----");
    }else{
        printf("-----Failure to insert-----");
    }

}
void testsearch()
{
    printf( "\n-----Testing search-----\n" );
    if(search(-3))
    {
        printf("\n'3' is in the tbale, test succeeded\n");
        testsPassed++;
    }else
    {   
        printf("\n'3' is  in the tbale, test failed\n");
        testsFailed++;
    }
    printf("\nsearch '500' in the tbale\n");
    if(search(500))
    {
        printf("\n'500' is not in the tbale, test failed\n");
        testsFailed++;   
    }else
    {   
        printf("\n'500' is not in the tbale, test succeeded\n");
        testsPassed++;
    }

    printf( "\n-----Testing search End-----\n" );
}

void testRemove()
{   
    printf( "\n-----Testing remove item-----\n" );
    #define testRemoveSize  6
    int remove[6]={7,-3,3,5,4,4};
    answer arr[testRemoveSize]={{{-3,3,4,5},4},{{3,4,5},3},
    {{4,5},2},{{4},1},{{},0},{{},0}
    };
    Boolean result[testRemoveSize]= {false,true,true,true,true,false};
    
    for(int i = 0; i < testRemoveSize; i++ )
    {   printf( "\nTesting removeItem: %d", remove[i] );
        if(removeItem(remove[i]) == result[i]){
            if(testMatched(arr[i].size,arr[i].output) && result[i]){
            printf("%d test removeItem successfully",i+1);
            }else{
            printf("can not remove %d, this item is not in table", remove[i]);
        }

        }
    }
    printf( "\n-----Testing remove item End-----\n" );

   
    
}

void testEmpty()
{   printf("\n------test empty set-----\n");
    clearTable( );
    int answer[0]={};
    if(testMatched(0,answer)){
        printf("\n-----successfully clear the table-----\n");
    }else
    {
        printf("\n-----failed to test clearTable -----\n");
    }
}

Boolean testMatched( int size, int arr[])
{
    int testresult = 0;
    Boolean result = false;
   if(size >= 0)
   {
       for(int i = 0; i < size; i++ )
       {
           if(search(arr[i])){

               testresult++;
           }
       }
   }else{
       printf("\ntest failed\n");
       testsFailed++;
   }
   if(testresult == size){
    printf("\ntest succeeded\n");  
    result = true;
    testsPassed++;
   }else
   {   printf("\ntest failed\n");
       testsFailed++;
   }
   return result;

}



