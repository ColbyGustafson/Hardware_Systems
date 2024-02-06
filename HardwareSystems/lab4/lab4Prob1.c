#include <stdio.h>

// This function prints the given number n in binary form
void printBinary(int n){
    int i;
    int arr[32];
    int len = 32;
    int mask = 1;
    int index = 0;
    while(len--){
        if(n&mask)
            arr[index] = 1;
        else
            arr[index] = 0;
        index++;
        mask <<= 1;
    }
    for(i=31; i>=0; i--){
        printf("%d",arr[i]);
        if(!(i%4))printf(" ");
    }
    printf("\n");
}

int getBitCounts(int x, int y)
{
	int count = 0;
	while(x > 0 | y > 0){
		int num1 = (x&1);
		int num2 = (y&1);
		if(num1 != num2)
			count++;
	x>>=1;
	y>>=1;
	}	
	return count;
} 

int main()
{

  int x, y;
  printf("Please enter the first number:");
  scanf("%d", &x);
  printf("Please enter the second number:");
  scanf("%d", &y);
  
  printf("The first number in binary is:\t");
  printBinary(x);
  printf("The second number in binary is:\t");
  printBinary(y);
  
  int bitCounts = getBitCounts(x,y);

  printf("Number of flips required to convert is %d \n", bitCounts);
  return 0;
}
