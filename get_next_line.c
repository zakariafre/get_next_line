/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zahrabar <zahrabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:34:16 by zahrabar          #+#    #+#             */
/*   Updated: 2025/11/12 16:49:43 by zahrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(char *buffer)
{
	int	i;

	i = 0;
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

char	*before_nl(char *buf)
{
	int		i;
	int		j;
	char	*new_buf;

	i = 0;
	if (!buf)
		return (NULL);
	while (buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	new_buf = malloc(i + 1);
	if (!new_buf)
		return (NULL);
	j = 0;
	while (buf[j] && buf[j] != '\n')
	{
		new_buf[j] = buf[j];
		j++;
	}
	if (buf[j] == '\n')
		new_buf[j++] = '\n';
	new_buf[j] = '\0';
	return (new_buf);
}

char	*after_nl(char *buf)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	j = 0;
	if (!buf)
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	buffer = malloc(ft_strlen(buf) - i + 1);
	if (!buffer)
		return (NULL);
	while (buf[i])
		buffer[j++] = buf[i++];
	buffer[j] = '\0';
	return (buffer);
}

static char	*ex_line(char **left_buf)
{
	char	*line;
	char	*tmp;

	line = before_nl(*left_buf);
	tmp = *left_buf;
	*left_buf = after_nl(*left_buf);
	free (tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			n;
	char		buffer[BUFFER_SIZE + 1];
	static char	*left_buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (left_buf && found_newline(left_buf))
		return (ex_line(&left_buf));
	n = 1;
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		buffer[n] = '\0';
		left_buf = ft_strjoin(left_buf, buffer);
		if (found_newline(left_buf) == 1)
			return (ex_line(&left_buf));
	}
	if (left_buf && left_buf[0])
	{
		line = left_buf;
		left_buf = NULL;
		return (line);
	}
	return (NULL);
}
