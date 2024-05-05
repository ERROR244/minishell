/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:45:12 by ksohail-          #+#    #+#             */
/*   Updated: 2024/01/31 21:21:48 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			readed;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) == -1
		|| BUFFER_SIZE > 0x7fffffff)
		return (0);
	line = NULL;
	readed = 1;
	while (readed > 0)
	{
		if (!buf[0])
			readed = read(fd, buf, BUFFER_SIZE);
		if (readed > 0)
			line = my_line(line, buf);
		if (check(buf))
			break ;
	}
	return (line);
}
