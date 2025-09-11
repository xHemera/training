#include <stdio.h>

int invalid(char *str)
{
	int opened = 0;
	int closed = 0;
	int i = 0;

	while(str[i])
	{
		if (str[i] == '(')
			opened++;
		else if (str[i] == ')')
			if (opened > 0)
				opened--;
			else
				closed++;
		i++;
	}
	return (closed + opened);
}

void solve(char *str, int must_fix, int fixed, int pos)
{
	int i = pos;
	char c;
	if (must_fix == fixed && !invalid(str))
	{
		puts(str);
		return ;
	}
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			c = str[i];
			str[i] = ' ';
			solve(str, must_fix, fixed + 1, i + 1);
			str[i] = c;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char *str = argv[1];
	solve(str, invalid(argv[1]), 0, 0);
}
