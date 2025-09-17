#include <stdio.h>

int invalid(char *str)
{
	int open = 0;
	int closed = 0;
	int i = 0;
	char c;

	while (str[i])
	{
		c = str[i];
		if (c == '(')
			open++;
		else if (c == ')')
		{
			if (open > 0)
				open--;
			else
				closed++;
		}
		i++;
	}
	return (open + closed);
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
			str[i] = '_';
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
	solve(str, invalid(str), 0, 0);
	return 0;
}
