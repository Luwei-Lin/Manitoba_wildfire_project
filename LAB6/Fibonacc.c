#include <stdio.h>
#include <stdlib.h>

long fib(int n)
{
  long result;
  
  if (n==0)
    result = 0;
  else if (n==1 || n==2)
    result = 1;
  else
    result = fib(n-1) + fib(n-2);
  
  return result;
}
int cache[30];

int fibcache(int n)
{   
    if(n == 0){
        return 0;
    }
    int ret = 0;
    if(n < 2)
    {
        ret = 1;
    }else if(cache[n])
    {
        ret = cache[n];
    }else
    {
        cache[n] = fibcache(n-1) + fibcache(n - 2);
        ret = cache[n];
    }
    return ret;
}

int main( int argc, char *argv[] )
{
  // we really should check the input...
  int fibNum = atoi(argv[1]);
  
  printf("The %d Fibonacci number is %ld\n", fibNum, fibcache(fibNum));
  
  return EXIT_SUCCESS;
}
