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
	while (str[i])
	{
		int j = i + 1;
		while(str[j])
		{
			if (str[i] > str[j])
				swap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}

void solve(char *str, int pos, int len)
{
	if (pos == len)
	{
		write(1, str, len);
		write(1, "\n", 1);
		return ;
	}
	sort(str + pos);
	int i = pos;
	while (i < len)
	{
		if (i != pos && str[i] == str[pos])
        {
            i++;
            continue;
        }
		swap(&str[pos], &str[i]);
		solve(str, pos + 1, len);
		swap(&str[pos], &str[i]);
		if (i < len - 1)
			sort(str + pos);
		i++;
	}
	return ;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	sort(argv[1]);
	solve(argv[1], 0, strlen(argv[1]));
	return 0;
}
