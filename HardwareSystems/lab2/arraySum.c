#include <stdio.h>
#define N 32

void fill1(int arr[], int n) {
	int i=0;
	for(i=0; i<n; i++) {
		arr[i] = i*2;
	}
}

void fill2(int arr[], int n) {
	int i=0;
	for(i=0; i<n; i++) {
		arr[i] = i*i;
	}
}

void fill3(int arr[], int arr1[], int arr2[], int n) {
	int i=0;
	for(i=0; i<n; i++) {
		arr[i] = arr1[i]+arr2[i];
	}
}

void show(int arr[], int n) {
	int i=0;
	for(i=0; i<n; i++) {
		printf("%d, ", arr[i]);
	}
	printf("\n");
}

int main() {
	int array1[N];
	fill1(array1, N);
	show(array1, N);
	
	int array2[N];
	fill2(array2, N);
	show(array2, N);

	int array3[N];
	fill3(array3, array1, array2, N);
	show(array3, N);
}