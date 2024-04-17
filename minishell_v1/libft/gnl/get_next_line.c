/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:07:51 by memahote          #+#    #+#             */
/*   Updated: 2022/12/20 14:21:31 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_gnl(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read(int fd, char *line)
{
	char	buffer[BUFFER_SIZE + 1];
	int		i;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (NULL);
		buffer[i] = '\0';
		line = ft_strjoin_gnl(line, buffer);
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*line;
	char			*linefinal;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) == -1)
		return (free(line), NULL);
	line = ft_read(fd, line);
	if (!line)
		return (NULL);
	linefinal = ft_extract(line);
	if (!linefinal)
		return (free(line), line = NULL, NULL);
	line = ft_reset(line);
	return (linefinal);
}
