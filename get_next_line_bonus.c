/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 23:10:53 by bsouhar           #+#    #+#             */
/*   Updated: 2022/11/17 18:46:26 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *buffer)
{
	char	buf[BUFFER_SIZE + 1];
	int		i;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			buffer = NULL;
			return (buffer);
		}
		buf[i] = '\0';
		buffer = ft_strjoin(buffer, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (buffer);
}

char	*n_stop(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*the_rest(char *buffer)
{
	char	*the_rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	the_rest = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i) + 1);
	while (buffer[i])
	{
		the_rest[j] = buffer[i];
		i++;
		j++;
	}
	the_rest[j] = '\0';
	free(buffer);
	return (the_rest);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd == 1 || fd == 2)
		return (0);
	buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (0);
	line = n_stop(buffer[fd]);
	buffer[fd] = the_rest(buffer[fd]);
	return (line);
}
