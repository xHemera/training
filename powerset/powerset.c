#include <stdio.h>
#include <stdlib.h>

int calc(int *nums, int n)
{
	int ret = 0;
	int i = 0;
	while (i < n)
	{
		ret += nums[i];
		i++;
	}
	return ret;
}

void print(int *nums, int n)
{
	int i = 0;
	while (i < n)
	{
		printf("%i", nums[i]);
		if (i < n - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

void solve(int *nums, int *subset, int size, int n, int subsize, int level)
{
	if (level == size)
	{
		if (calc(subset, subsize) == n)
			print(subset, subsize);
		return ;
	}
	subset[subsize] = nums[level];
	solve(nums, subset, size, n, subsize + 1, level + 1);
	solve(nums, subset, size, n, subsize, level + 1);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	int size = argc - 2;
	int n = atoi(argv[1]);
	int i = 0;
	int *nums = malloc(sizeof(int) * size);
	int *subset = malloc(sizeof(int) * size);

	while (i < size)
	{
		nums[i] = atoi(argv[i + 2]);
		i++;
	}
	solve(nums, subset, size, n, 0, 0);
	free(nums);
	free(subset);
}
