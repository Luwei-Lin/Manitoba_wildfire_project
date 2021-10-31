//-----------------------------------------
// NAME: Luxiang Lin
// STUDENT NUMBER: 7900607
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Mehdi Niknam
// ASSIGNMENT: 3
//
// REMARKS: black box test.
//
//-----------------------------------------
#include "set.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_SIZE 50

void testEmpty();
void testInsert();
void testRemove();

void testUnion();
void testDisjoint();
void testSymmetricDifferenceOf();
Boolean testEqual();
Set *buildSet();
void testcheckSets();


typedef struct
{
  int output[MAX_SIZE];
  int size; 
  int input_1[MAX_SIZE];
  int input_1Size;
  int input_2[MAX_SIZE];
  int input_2Size;
} TestCase;

static int testPassed;
static int testFailed;


int main()
{   printf("-----Start tests-----");
    testEmpty();
    testInsert( );
    testRemove( );
    testUnion( );
    testDisjoint( );
    testSymmetricDifferenceOf();
    printf("\ntotal Passed: %d\n", testPassed);
    printf("\ntotal Failed: %d\n", testFailed);
    printf("-----End tests-----");
    return 0;

}
void testEmpty()
{   
    printf("\n------test empty set-----\n");
    int empty[0] = {};
    Set *new_Set = newSet();
    assert(new_Set);
    if(testEqual(new_Set,0,empty))
    {
       
        printf("\nThe empty set was successfully tested\n");
    }else
    {
        printf("\nFailed to test an empty set\n");
    }
    deleteSet(new_Set);
    testcheckSets();

}

void testInsert( )
{   
    #define testInsertSize  5
    printf("\n------test insert items-----\n");
    int input[testInsertSize] = {3,8,3,1,2};
    TestCase expectOutput[testInsertSize]={
        {{3},1,{},0,{},0}, {{3,8},2,{},0,{},0}, 
        {{3,8},2,{},0,{},0},{{3,8,1},3,{},0,{},0},{{3,8,1,2},4,{},0,{},0}
    };
    Boolean result[testInsertSize]= {true, true, false, true, true};
    Set *new_Set = newSet();
    assert(new_Set != NULL);
    for(int i = 0; i < testInsertSize; i++)
    {
        if(insertItem(new_Set, input[i]) == result[i])
        {  
            if(testEqual(new_Set,expectOutput[i].size, expectOutput[i].output)){
                printf("\nThe number %d was successfully inserted\n", input[i]);
                testPassed++;
            }else{
                printf("\nFailed to insert %d\n", input[i]);
                testFailed++;
            }
        }else
        {
            
            printf("\n the set is unequal to expect set, %d can not work\n",input[i]);
            testFailed++;
        }
    }
    deleteSet(new_Set);
    testcheckSets();
}
void testRemove()
{
    #define testRemoveSize  5
    printf("\n------test remove items-----\n");
    int input[testRemoveSize] = {3,8,2};
    TestCase expectOutput[testRemoveSize]={
        {{3,8,2},3,{},0,{},0}, {{3,8},2,{},0,{},0}, 
        {{3},1,{},0,{},0},{{},0,{},0,{},0},{{},0,{},0,{},0}
    };
    int remove[testRemoveSize]={7,2,8,3,3};
    Boolean result[testRemoveSize]= {false,true,true,true,false};
    Set *new_Set = buildSet(3,input);

    assert(new_Set);
    for(int i = 0; i < testRemoveSize; i++)
    {
        if(removeItem(new_Set, remove[i]) == result[i])
        {  
            if(testEqual(new_Set, expectOutput[i].size, expectOutput[i].output)){
            //printf("\nThe number %d was successfully remove\n", input[i]);
            //testPassed++;
                if(result[i]){
                     printf("\nSuccessfully remove number %d ,this number is  in set\n",remove[i]);
                }else{
                    printf("\nCan not remove number %d ,this number is not in set\n",remove[i]);       
                }
            }else{
                printf("\nthe set is unequal to expect set\n");
                testFailed++;
            }
        }else
        {
            printf("\nFailed to remove %d\n", remove[i]);
            testFailed++;
        }
    }
    deleteSet(new_Set);
    testcheckSets();
}


void testDisjoint()
{
    #define testDisjoint 7
    printf("\n-----test Disjoint-----\n");
    
    TestCase expectOutput[testDisjoint]= {
    {{},0,{},0,{},0},{{},0,{},0,{5},1} ,{{},0,{1,2,3},3,{3,2,1},3},
     {{},0,{1,2},2,{2,3,4},3}, {{},0,{1,2,3,4},4,{5,6},2}, {{},0,{3},1,{3},1}, 
    {{},0,{},0,{2,3,4},3}
    };
    Boolean result[testDisjoint] = {true , true, false, false, true,false, true};
   
    for (int i = 0; i < testDisjoint; i++)
     {  
        Set *new_one;        
        Set *new_two;
        new_one = buildSet(expectOutput[i].input_1Size, expectOutput[i].input_1);
        new_two = buildSet(expectOutput[i].input_2Size, expectOutput[i].input_2);
        assert(new_one);
        assert(new_two);
        printf("\n------test %d disjoint item-----\n",i+1);

        if(areDisjoint(new_one,new_two) == result[i])
        {
           //printf("\n------test %d disjoint item-----\n",i+1);
            if(result[i]){
                     printf("\nThis two set is disjoint\n");
                     testPassed++;
                }else{
                    printf("\nThis two set is Not disjoint\n"); 
                    testPassed++;      
                }
        }else
        {   
                printf("\nthe set is unequal to expect set\n");
                testFailed++;
        }
        deleteSet(new_one);
        deleteSet(new_two);
    }
   
    testcheckSets();
}

void testUnion()
{
    #define testUnion  6
    printf("\n------test Union items-----\n");
    TestCase expectOutput[testUnion]= {
    {{},0,{},0,{},0},{{1,2},2,{1},1,{2},1} ,{{1,2,3},3,{1,2,3},3,{3,2,1},3}, {{1,2,3},3,{1,2},2,{2,3},2}, 
    {{3},1,{3},1,{3},1},{{2,3,4,5,6},5,{3},1,{2,4,5,6},4} 
    };
    Set *new_one;        
    Set *new_two;
    Set *UnionSet; 
    for (int i = 0; i < testUnion; i++)
     {   printf("\n------test %d Union item-----\n",i+1);
        new_one = buildSet(expectOutput[i].input_1Size, expectOutput[i].input_1);
        new_two = buildSet(expectOutput[i].input_2Size, expectOutput[i].input_2);
        assert(new_one);
        assert(new_two);

        UnionSet = unionOf(new_one,new_two);
        assert(UnionSet);

        if(testEqual(UnionSet,expectOutput[i].size, expectOutput[i].output))
        {
          
            
            printf("\nThe two sets form an UnionSet\n");
            deleteSet(UnionSet);
            //testPassed++;      
                
        }else
        {   
            printf("\nthe set is unequal to expect set\n");
            deleteSet(UnionSet);
            //testFailed++;
        }
        deleteSet(new_one);
        deleteSet(new_two);
    }
    
    testcheckSets();
}

void testSymmetricDifferenceOf()
{
    #define testSymmetricDifference  5
    printf("\n------test SymmetricDifference of set-----\n");
    TestCase expectOutput[testSymmetricDifference]= {
    {{},0,{},0,{},0},{{1,2,3},3,{1,2,3},3,{},0},{{},0,{1,2},2,{1,2},2} ,  
    {{},0,{3},1,{3},1},{{2,6},2,{4,5},2,{2,4,5,6},4} 
    };
    Set *new_one;        
    Set *new_two;
    Set *SymmetricSet; 
    for (int i = 0; i < testSymmetricDifference; i++)
     {   printf("\n------test %d SymmetricDifferenc item-----\n",i+1);
        new_one = buildSet(expectOutput[i].input_1Size, expectOutput[i].input_1);
        new_two = buildSet(expectOutput[i].input_2Size, expectOutput[i].input_2);
        assert(new_one);
        assert(new_two);

        SymmetricSet = symmetricDifferenceOf(new_one,new_two);
        assert(SymmetricSet);

        if(testEqual(SymmetricSet,expectOutput[i].size, expectOutput[i].output))
        {
          
            
            printf("\nThe two sets form an NewSet\n");
            deleteSet(SymmetricSet);
            //testPassed++;      
                
        }else
        {   
            printf("\nthe set is unequal to expect set\n");
            deleteSet(SymmetricSet);
            //testFailed++;
        }
        deleteSet(new_one);
        deleteSet(new_two);
    }
    
    testcheckSets();
}



Set *buildSet( const int size, const int items[] )
{
    Set *new_Set = newSet();
  
    if (new_Set)
    {
        for (int i=0; i<size; i++){
        insertItem(new_Set, items[i]);
        }
    }
    assert(new_Set); 
    return new_Set;
}


void testcheckSets( )
{

   if(validateMemUse())
   {    printf("\nThe set has been cleared\n");
        testPassed++;
   }
   else
   {   printf("\nThe set has not been Completely cleared\n");
       testFailed++;
   }
   
}

Boolean testEqual( Set const * const setA,  int size, int items[])
{   
    Boolean result = false;
    Set *contrastSet = buildSet(size, items);
    assert(contrastSet);
    printf("\nVerify that the set is the same as expected\n");
    if(areEqual(setA, contrastSet))
    {
        printf("\nthe set is the same as expected\n");
        result = true;
        testPassed++;
       
    }else
    {
        printf("\nthe set is NOT the same as expected\n");
        testFailed++;
       
    }
    deleteSet(contrastSet);
    return result;
}



