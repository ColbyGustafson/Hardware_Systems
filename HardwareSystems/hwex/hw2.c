#include <stdio.h>

void printCombo(int x, int y){
	int z = 0;
	int i;
	int j;
	int mask = 1;
	for(i=0;i<16;i+=2 ){
		z = z|getBit(x,i)<<i;
	}
	for(j=1;j<16;j+=2 ){
		z = z|getBit(y,j)<<j;
        }
	printf("%d\n",&z);	
}

int getBit(int num, int i){
	int shifted = 1<<i;
	num = num & shifted;
	if(num!=0)
		return 1;
	else
		return 0;
}

void main(){
	int x, y;
	printf("Please enter the first number:");
	scanf("%d", &x);
	printf("Please enter the second number:");
	scanf("%d", &y);

	printf("The combined bits from both numbers is: ");
	printCombo(x,y);
}
