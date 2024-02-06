# include <stdio.h>
# define EOL '\0'

void main() 
{
	int len;
	printf("Amount: ");
	scanf("%d", &len);
	int arr1[len];

	int i;
	for(i=0; i<len; i++)
	{
		printf("\nInput %d: ", i+1);
		scanf("%d", &arr1[i]);
	}
	int j;
	for(j = len-1; j>=0; j--)
	{
		printf("%d ", arr1[j]);
	}
}
