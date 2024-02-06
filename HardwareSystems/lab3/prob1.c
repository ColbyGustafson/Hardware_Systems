# include <stdio.h>
# define EOL '\0'

void main() 
{
	char word[20];
	char output[20];
	printf("Enter lowercase letters and/or positive integers:\n");
	scanf("%s", word);
	int i = 0;
	for(i=0; word[i] != EOL; i++)
	{
		if(word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u'|| word[i] == '0' || word[i] == '2' || word[i] == '4' || word[i] == '6' || word[i] == '8')
		{
			printf("%c",word[i]);
		}
	}
}
