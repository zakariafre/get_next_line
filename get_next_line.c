/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zahrabar <zahrabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:34:16 by zahrabar          #+#    #+#             */
/*   Updated: 2025/11/11 14:42:29 by zahrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (buf[i] && buf[i] != '\n')
	{
		i++;
	}
	i++;
	new_buf = malloc(i + 1);
	if (!new_buf)
		return (NULL);

	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		new_buf[i] = buf[i];
		i++;
	}
	new_buf[i] = '\0';
	return (new_buf);
}

char *after_nl(char *buf)
{
	int	i;
	char *buffer;

	if (!buf)
		return (NULL);
	buffer = buf;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			i++;
			return (&buffer[i]);
		}
		i++;
	}
	free(buf);
	return (NULL);
}

char *get_next_line(int fd)
{
	int n;
	char *buffer = malloc(BUFFER_SIZE + 1);
	static char *left_buf = NULL;
	char *line = NULL;

	if (found_newline(line) == 1)
	{
		left_buf = after_nl(line);
		line = before_nl(line);
	}
	
	n = read(fd, buffer, BUFFER_SIZE);
	if (n == 0)
		return (NULL);
	if (n == -1)
		return (NULL);
	buffer[n] = '\0';

	line = ft_strjoin(left_buf, buffer);
	free(buffer);
	free(left_buf);
	return (line);
}
