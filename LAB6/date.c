#include <stdio.h>
#include <string.h>
// int main()
// {
//     int month, year, day;
//     scanf("%d %d %d",&month, &day, &year);
//     printf("%d-%d-%d %d  %d",month, day,year,);
//     return 0;
// }

int main () {

    int a, b, c;
    char arr[100] = {0};
    char enter[100] = {0};
    scanf("%s", enter);
    sscanf(enter, "%d-%d-%d", &a, &b, &c);
    if(a>10 && b>10){
        sprintf(arr, "%d%d%d", a, b, c);
    }else if(b >10 &&a<10)
    {
        sprintf(arr, "0%d%d%d", a, b, c);
    }
    else if(a>10 && b<10)
    {
        sprintf(arr, "%d0%d%d", a, b, c);
    }else{
         sprintf(arr, "0%d0%d%d", a, b, c);
    }
 
    //sprintf(arr, "%d0%d%d", a, b, c);
    int ans = 0;
    for (int i = 0; i < strlen(arr); i++) {
        ans = (ans << 4) + (arr[i] - '0');
        printf("ans %d\n", ans);
    }


    printf("%s\n", arr);
    return 0;
}
/*
int main(){
	int n,a,b;
	scanf("%d",&n);
	a = n/16;
	b = n%16;
	printf("%d",a*10+b);
	return 0;
}
*/
