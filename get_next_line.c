/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:34:16 by zahrabar          #+#    #+#             */
/*   Updated: 2025/11/11 22:21:32 by marvin           ###   ########.fr       */
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
	int i;
	int j;
	char *new_buf;

	i = 0;
	if (!buf)
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	new_buf = malloc(i + 1);
	if (!new_buf)
		return (NULL);

	j = 0;
	while (buf[j + 1] != '\n')
	{
		new_buf[j] = buf[j];
		j++;
	}
	new_buf[j] = '\0';
	return (new_buf);
}

char *after_nl(char *buf)
{
	int i;
	int j;
	char *buffer;
	int nl;

	i = 0;
	j = 0;
	if (!buf)
		return (NULL);
		
	while (buf[i])
	{
		if (buf[i] == '\n')
			nl = i;
		i++;
	}
	nl++;
	buffer = malloc(ft_strlen(buf) - nl + 1);
	if (!buffer)
		return (NULL);
	while(buf[i])
	{
		buffer[j] = buf[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	return (buffer);
}

char *get_next_line(int fd)
{
	char *line;
	int n;
	static char *left_buf;
	char buffer[BUFFER_SIZE + 1];

	n = 0;
	left_buf = NULL;

	if (found_newline(left_buf) == 1)
	{
		line = before_nl(left_buf);
		char *tmpo = left_buf;
		left_buf = after_nl(line);
		free(tmpo);
		return (line);
	}
	
	while ((n = read(fd, buffer, BUFFER_SIZE) > 0) && *buffer != '\0')
	{
		buffer[n] = '\0';
		left_buf = ft_strjoin(left_buf, buffer);
		
		if (found_newline(left_buf) == 1)
		{
			line = before_nl(left_buf);
			char *tmpo = left_buf;
			left_buf = after_nl(line);
			free(tmpo);
			return (line);
		}
	}

	if (left_buf && *left_buf)
	{
		line = left_buf;
		left_buf = NULL;
		return (line);
	}

	return (NULL);
}
