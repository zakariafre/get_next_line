/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zahrabar <zahrabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:34:16 by zahrabar          #+#    #+#             */
/*   Updated: 2025/11/15 18:51:03 by zahrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_nl(char *buffer)
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

char	*ex_line(char **saved_buf)
{
	char	*line;
	char	*new_saved;
	char	*tmp;

	if (!*saved_buf)
		return (NULL);
	if ((*saved_buf)[0] == '\0')
		return (flush_leftover(saved_buf));
	tmp = *saved_buf;
	line = before_nl(tmp);
	if (!line)
		return (NULL);
	new_saved = after_nl(tmp);
	if (!new_saved)
	{
		free(line);
		return (NULL);
	}
	*saved_buf = new_saved;
	free (tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	static char	*saved_buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved_buf = read_join(saved_buf, buf, fd);
	if (!saved_buf || !saved_buf[0])
	{
		free(saved_buf);
		saved_buf = NULL;
		return (NULL);
	}
	tmp = ex_line(&saved_buf);
	if (!tmp)
	{
		free(saved_buf);
		saved_buf = NULL;
		return (NULL);
	}
	return (tmp);
}
