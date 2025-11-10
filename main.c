#include "get_next_line.h"

int found_newline(char *buffer)
{
	int i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}


char *before_nl(char *buf)
{
	int i = 0;
	char *new_buf;
	while(buf[i] && buf[i] != '\n')
	{
		i++;
	}
	new_buf = malloc(i + 1);
	if (!new_buf)
		return (NULL);

	i = 0;
	while(buf[i] && buf[i] != '\n')
	{
		new_buf[i] = buf[i];
		i++;
	}
	return (new_buf);
}


char *get_line(int fd)
{
	int n;
	char *buffer = malloc(BUFFER_SIZE + 1);
	static char *stash = NULL;
	static char *left_stash = NULL;

	n = read(fd, buffer, BUFFER_SIZE);
	if (n <= 0)
		return (NULL);
	buffer[n] = '\0';

	stash = ft_strjoin(stash, buffer);
	if (found_newline(stash) == 1)
	{
		left_stash = ft_strchr(stash, '\n');
		stash = before_nl(stash);
	}
	return (stash);
}

int main()
{
	int fd;
	fd = open("file.txt", O_RDWR | O_CREAT, 0777);
	if (fd < 0)
		return 1;

	char *line = get_line(fd);

	printf("first line : %s\n", line);
	printf("first line : %s\n", line);

	// free(line);
	close(fd);
	return (0);
}
