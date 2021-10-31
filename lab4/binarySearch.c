#include<stdio.h>
#include<assert.h>
/*
1. Comment on the programming style used in this column, and in this book, in general.
Address issues such as the variable names, the form and specification of the
binary search function, the code layout and so forth.
2. Translate the pseudocode description of binary search into languages other than C,
and build scaffolding to test and debug your implementation. How do the language
and system help and hinder?



Initialization, The invariant is true when the loop is executed for the first time.
Preservation. If the invariant holds at the beginning of an iteration and the loop
body is executed, then the invariant will remain true after the loop body finishes
execution.
Termination. The loop will terminate and the desired result will hold (in this case,
the desired result is that p has the correct value). Showing this will use the facts
established by the invariant.

1. { mustbe(0, n-1) }
2. 1 = 0; u = n-1
3. { mustbeO , u) }
4. loop
5. { mustbeO , u) }
6. if 1 > u
7. { 1 > u && mustbeO , u) }
8. { t is not in the array }
9. p = -1; break
10. { mustbeO, u) && 1 <= u }
11. m = O + u) / 2
12. { mustbeO, u) && 1 <= m <= u }
13. case
14. x[m] < t:
15. { mustbeO, u) && cantbe(0, m) }
16. { mustbe(m+l, u) }
17. 1 = m+1
18. { mustbeO , u) }
19. x[m] == t:
20. { x[m] == t }
21. p = m; break
22. x[m] > t:
23. { mustbeO, u) && cantbe(m, n) }
24. { mustbeO, m-1) }
25. u = m-1
26. { mustbeO , u) }
27. { mustbeO, u) }
*/

#define MAXN 100

typedef int DataType;
int n;
int t;
int size;
int oldsize;
DataType x[MAXN];

int binarySearch(DataType t);
int sorted();
void test();
void autotest();
#define s binarySearch

void test(){

    while(scanf("%d %d", &n, &t) != EOF)
    {
        for(int i = 0; i < n; i++)
        {
            x[i] = 10 * i;
        }
        printf("%d\n", binarySearch(t));
    }

}//test end

void autotest()
{
    for(int i = 0; i < MAXN; i++)
        {
            n = i;
            printf("n=%d\n", n);
        // test distinct elements (plus one at the end)
        for(int i = 0; i <= n; i++)
            {   
                x[i] = 10 *i;
                
            }
        for(int i = 0; i < n; i++)
            {
                assert(s(10*i)      == i);
                assert(s(10*i - 5) == -1);
            
            }
        
    assert(s(10*n - 5) == -1);
    assert(s(10*n)     == -1);
        
        // test equal elemnts

        for(int i = 0; i < n; i++)
        {
           x[i] =10;
        } 
        //x[0]=0;
        if(n == 0) 
             assert(s(10) == -1);
        else
            assert(0 <= s(10) && s(10) < n);
        assert(s(5) == -1);
        assert(s(15) == -1);     

        }   

}

int main()
{
    
   // test();
    autotest();
    int x[6] = {2,4,5,2,3,4};
    binarySearch(4);
    
}

int sorted()
{
    int i;
    for(i = 0; i < n - 1; i++)
    {
        if(x[i] > x[i+1])
            return 0;
    }
    return 1;
}
//t is target item
int binarySearch(DataType t)
{
    assert(sorted() == 1);
    int low, up, mid;
    low = 0;
    up = n - 1;
    size = n + 1;

    while(low <= up)
    {
        mid = (low + up) / 2;
        if(x[mid] < t)
        {
            low = mid + 1;
        }
        else if (x[mid] == t)
        {
            assert(0 <= mid && mid < n && x[mid] == t);
            return mid;
        }
        else
        {
            up = mid - 1;
        }
    }
    oldsize = size;
    size = up - low + 1;

    assert(size < oldsize);
    assert((up< 0 || x[up] < t) && (up+1>= n|| x[up+1] > t));

    return -1;
}





    