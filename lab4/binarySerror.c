#include<stdio.h>
#include<assert.h>
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
            //x[i] = 10 * i;//
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
        x[0]=0;
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
    int l, u, m;
    l = -1;//
   // l = 0;
    u = n - 1;

   //size = n + 1;//*
    while(l <= u)
    {
        m = (l + u) / 2;
        if(x[m] < t)
        {
            l = m + 1;
        }
        else if (x[m] == t)
        {
            assert(0 <= m && m < n && x[m] == t);
            return m;
        }
        else
        {
            u = m - 1;
        }
    }
    oldsize = size;
    size = u - l + 1;

    assert(size < oldsize);
    assert((u< 0 || x[u] < t) && (u +1>= n|| x[u+1] > t));

    return -1;
}
