/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:11:19 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/10/05 16:11:23 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_a_line(int fd, char *buf, int ret)
/*Reads BUFFER_SIZE bytes from the file and appends the buffer to the output  *
 *line. The loop checks if there's a newline present and then splits it into  *
 *the line to be printed and the remaining buffer.*/
{
	char	*readbuf;
	char	*line;

	readbuf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!readbuf)
		return (NULL);
	readbuf[0] = '\0';
	line = ft_strdup(buf);
	if (!line)
		return (NULL);
	while (ret > 0 && ft_strchr(line, '\n') == NULL)
	{
		ret = read(fd, readbuf, BUFFER_SIZE);
		if (ret > 0)
		{
			readbuf[ret] = '\0';
			line = ft_strjoin_free(line, readbuf);
			if (!line)
				return (NULL);
		}
	}
	free(readbuf);
	if (ret < 0 || (ret == 0 && ft_strlen(line) == 0))
		return (free(line), line = NULL, NULL);
	return (line);
}

static char	*split_buf(char *line, char **buf)
{
	int		i;
	char	*temp;

	temp = ft_strdup(line);
	if (!temp)
		return (NULL);
	free(line);
	i = 0;
	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	if (ft_strchr(temp, '\n'))
	{
		*buf = ft_strdup(ft_strchr(temp, '\n') + 1);
		if (!*buf)
			return (NULL);
		while (temp[i] != '\n')
			i++;
		temp[++i] = '\0';
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf)
	{
		buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return (NULL);
		buf[0] = '\0';
	}
	line = get_a_line(fd, buf, 1);
	if (line == NULL)
	{
		if (buf)
			free (buf);
		return (buf = NULL, NULL);
	}
	else
		line = split_buf(line, &buf);
	return (line);
}
