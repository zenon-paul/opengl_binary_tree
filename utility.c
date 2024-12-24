#include<stdio.h>
#include<stdlib.h>
#include"utility.h"

int max_(int a,int b){
	return a>b?a:b;
}

int min_(int a,int b){
	return a<b?a:b;
}

int factorial(int n){
	if (n<=1) return 1;
	return n*factorial(n-1);
}

int permutation_num(int* num,int n){
	int ind = 0;
	for(int i = 0;i < n;i++){
		ind *= (n-i);
		for(int j = i+1;j<n;j++){
			if(num[i]>num[j]) ind++;
		}
	}
	return ind;
}

void clear(int *array,int n){
	for(int i = 0;i<n;i++) array[i] = 0;
}

static void calculate_permutation(int** list,int* nums,int* seen,int seed,int n,int depth){
	seen[seed] = 1;
	nums[depth] = seed;
	for(int i = 1;i <= n;i++){
		if(seen[i] == 0){
			calculate_permutation(list,nums,seen,i,n,depth+1);
			seen[i] = 0;
		}
	}
	if(depth == n-1) for(int i = 0;i<n;i++) list[permutation_num(nums,n)][i] = nums[i];
	
}

void set_permutation_list(int** list, int n) {
	int fact = factorial(n);

	for (int i = 1; i <= n; i++) {
		int* seen = (int*)calloc(sizeof(int), (n + 1));
		int* nums = (int*)calloc(sizeof(int), (n + 1));
		calculate_permutation(list, nums, seen, i, n, 0);
		free(seen);
		free(nums);
	}
}

void permutation_test() {
	int n;
	int fact;
	int** list;
	printf("input a number");
	scanf("%d", &n);
	fact = factorial(n);
	list = (int**)malloc(sizeof(int*) * fact);
	for (int i = 0; i < fact; i++) list[i] = (int*)malloc(sizeof(int) * n);

	set_permutation_list(list, n);

	for (int i = 0; i < fact; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ",list[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');

	for (int i = 0; i < fact; i++) free(list[i]);
	free(list);
}