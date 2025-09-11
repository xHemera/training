#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int ft_strncmp(char *s1, char *s2, int n)
{
	int i = 0;
	while (i < n && s1[i] == s2[i])
		i++;
	return (i == n);
}

void process_buffer(char *filter, char *buffer, int len)
{
	int i = 0;
	int j;
	while(buffer[i])
	{
		if (ft_strncmp(filter, &buffer[i], len))
		{
			j = 0;
			while(j < len)
			{
				write(1, "*", 1);
				j++;
			}
			i+=len;
		}
		else
			write(1, &buffer[i++], 1);
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char c;
	char *buffer = malloc(1000000);
	char *filter = argv[1];
	int len = strlen(argv[1]);
	int pos = 0;

	while(read(0, &c, 1) > 0)
	{
		buffer[pos++] = c;
		if (c == '\n')
		{
			buffer[pos] = '\0';
			process_buffer(filter, buffer, len);
			pos = 0;
		}


	}
	if (pos > 0)
	{
		buffer[pos] = '\0';
		process_buffer(filter, buffer, len);
	}
	free(buffer);
	return 0;
}
