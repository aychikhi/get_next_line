/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:23:46 by aychikhi          #+#    #+#             */
/*   Updated: 2024/11/29 07:20:09 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buffer, char *remainder)
{
	char	*temp;
	ssize_t	bytes_read;

	temp = NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (remainder);
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		free(remainder);
		remainder = temp;
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	return (remainder);
}

static char	*extract_line(char **remainder)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		line = ft_substr(*remainder, 0, newline_pos - *remainder + 1);
		temp = ft_strdup(newline_pos + 1);
		free(*remainder);
		*remainder = temp;
	}
	else
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	remainder = read_line(fd, buffer, remainder);
	if (!remainder)
		return (NULL);
	return (extract_line(&remainder));
}
