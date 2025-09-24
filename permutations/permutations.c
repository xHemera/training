#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void	swap(char *s, char *ss)
{
	char tmp = *s;
	*s = *ss;
	*ss = tmp;
}

void	sort(char *s)
{
	int i = 0;
	int j = 0;
	while(s[i])
	{
		j = i + 1;
		while(s[j])
		{
			if(s[i] > s[j])
				swap(&s[i], &s[j]);
			j++;
		}
		i++;
	}
}

void	print(char *s, int n)
{
	write(1, s, n);
	write(1, "\n", 1);
}

void	solve(char *s, int start, int n)
{
	int i = 0;
	if(start == n)
	{
		print(s, n);
		return ;
	}
	i = start;
	while(i < n)
	{
		swap(&s[start], &s[i]);
		solve(s, start + 1, n);
		swap(&s[start], &s[i]);
		i++;
	}
}


int main(int ac, char **av)
{
    if(ac < 2)
        return 1;

    char *s = strdup(av[1]);
    int n = strlen(av[1]);
    sort(s);
    solve(s, 0, n);
    free(s);
    return 0;
}
