#include "get_next_line.h"

int mini_atoi(char *str)
{
	int rst = 0;

	while (*str)
		rst = (rst * 10) + *str++ - 48;
	return rst;
}

int main(int ac, char **av)
{
	char *line;
	int status = 1;
	int i = 0;

	int max = mini_atoi(av[2]);

	while (i < ac)
	{
		printf("av %d :%s\n", i, av[i]);
		i++;
	}
	int fd = open(av[1], O_RDONLY);

	printf("OPEN_MAX = %d\n", OPEN_MAX);
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	printf("\n");

	i = 0;
	while (i < max)
	{
		status = get_next_line(fd, &line);
		printf("line = %s\n", line);
		printf("status = %d\n", status);
		printf("\n");
		free (line);
		i++;
	}
}