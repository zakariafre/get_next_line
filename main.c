/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zahrabar <zahrabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 05:38:46 by zahrabar          #+#    #+#             */
/*   Updated: 2025/11/14 15:57:00 by zahrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
// #include <stdio.h>

// int main()
// {
// 	int fd;
// 	fd = open("test.txt", O_RDWR | O_CREAT, 0777);
// 	if (fd < 0)
// 		return 1;

// 	char *line;
// 	int i = 1;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("line %d : %s",i, line);
// 		i++;
// 		free(line);
// 	}

// 	close(fd);
// 	return (0);
// }