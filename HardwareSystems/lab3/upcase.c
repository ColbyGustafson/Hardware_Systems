# include <stdio.h>
# define EOL '\0'

void main() {
	int i = 0;
	char word[20];
	printf("Enter a lowercase word:\n");
	scanf("%s", word);

	for(i=0; word[i] != EOL; i++) {
		word[i] -= 32; // Hint: Look into ASCII values to understand why
	}

	//see what happens when you uncomment the line below for intputs greater than 3
	//word[3] = EOL;

	printf("Upcased word: %s \n", word);
}
