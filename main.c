#include "get_next_line.h"

int main()
{
	int fd;
	fd = open("test.txt", O_RDWR | O_CREAT, 0777);
	if (fd < 0)
		return 1;

	char *line = get_next_line(fd);

	printf("first line : %s\n", line);

	close(fd);
	return (0);
}
