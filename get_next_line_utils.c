/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zahrabar <zahrabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:48:04 by zahrabar          #+#    #+#             */
/*   Updated: 2025/11/12 02:09:39 by zahrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;
	int		len;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	str = (char *)s1;
	len = ft_strlen(str);
	s2 = malloc(len + 1);
	if (!s2)
		return (NULL);
	while (str[i])
	{
		s2[i] = str[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}

char	*flush_leftover(char **what_left)
{
	char	*line;

	line = *what_left;
	*what_left = NULL;
	return (line);
}

char	*read_join(char *left_buf, char *buf, int fd)
{
	char	*tmp;
	int		n;

	n = 1;
	while (found_newline(left_buf) == 0 && n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
		{
			free(left_buf);
			left_buf = NULL;
			return (NULL);
		}
		buf[n] = '\0';
		tmp = left_buf;
		left_buf = ft_strjoin(left_buf, buf);
		if (!left_buf)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
	}
	return (left_buf);
}
