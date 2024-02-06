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

int getPairity(int x)
{
	int pairity = 0;
	while(x > 0){
		if(x&1){
			if(pairity == 1)
				pairity = 0;
			else
				pairity = 1;
		}
		x>>=1;
	}
	return pairity; // should either be 0 or 1 for even or odd
}

int main()
{

  int x;
  printf("Please enter the number to check pairity:");
  scanf("%d", &x);
  
  printf("The entered number in binary is:\t");
  printBinary(x);
  
  int pairity = getPairity(x);

  if(pairity == 0) {
    printf("The pairity of entered number is even.\n");
  } else {
    printf("The pairity of entered number is odd.\n");
  }
  
  return 0;
}
