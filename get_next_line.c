/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zahrabar <zahrabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:34:16 by zahrabar          #+#    #+#             */
/*   Updated: 2025/11/14 15:24:27 by zahrabar         ###   ########.fr       */
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
	if (!buf || !buf[0])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	new_buf = malloc(i + 1);
	if (!new_buf)
		return (NULL);
	i = 0;
	j = 0;
	while (buf[j] && buf[j] != '\n')
		new_buf[j++] = buf[i++];
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

char	*ex_line(char **what_left)
{
	char	*line;
	char	*new_left;
	char	*tmp;

	if (!*what_left)
		return (NULL);
	if ((*what_left)[0] == '\0')
		return (flush_leftover(what_left));
	tmp = *what_left;
	line = before_nl(tmp);
	if (!line)
		return (NULL);
	new_left = after_nl(tmp);
	if (!new_left)
	{
		free(line);
		return (NULL);
	}
	*what_left = new_left;
	free (tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	static char	*what_left;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	what_left = read_join(what_left, buf, fd);
	if (!what_left || !what_left[0])
	{
		free(what_left);
		what_left = NULL;
		return (NULL);
	}
	tmp = ex_line(&what_left);
	if (!tmp)
	{
		free(what_left);
		what_left = NULL;
		return (NULL);
	}
	return (tmp);
}
