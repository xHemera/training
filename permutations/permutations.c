#include <string.h>
#include <unistd.h>

void swap(char *s1, char *s2)
{
	char tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void sort(char *str)
{
	int i = 0;
	int j = 0;
	while (str[i])
	{
		j = i + 1;
		while(str[j])
		{
			if (str[i] > str[j])
				swap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}

void solve(char *str, int start, int len)
{
	int i = start;
	if (start == len)
	{
		write(1, str, len);
		write(1, "\n", 1);
		return ;
	}
	while (i < len)
	{
		swap(&str[start], &str[i]);
		solve(str, start+1, len);
		swap(&str[start], &str[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	char *str = argv[1];
	int len = strlen(str);
	sort(str);
	solve(str, 0, len);
	return 0;
}

