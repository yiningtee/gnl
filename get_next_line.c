/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytee <ytee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:49:04 by ytee              #+#    #+#             */
/*   Updated: 2026/08/29 17:49:04 by ytee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *line)
{
	char	*buffer;
	int		readbyte;

	buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	readbyte = 1;
	while (!ft_strchr(line, '\n') && readbyte > 0)
	{
		readbyte = read(fd, buffer, BUFFER_SIZE);
		if (readbyte == -1)
		{
			free (buffer);
			free (line);
			return (NULL);
		}
		buffer[readbyte] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free (buffer);
	return (line);
}

static char	*extract_line(char *line)
{
	int		i;
	char	*box;

	if (!line || !line[0])
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	box = (char *)malloc(sizeof(char) * (i + 2));
	if (!box)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		box[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		box[i] = line[i];
		i++;
	}
	box[i] = '\0';
	return (box);
}

static char	*clean_line(char *line)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
	{
		free (line);
		return (NULL);
	}
	ptr = (char *)malloc(ft_strlen(line) - i + 1);
	if (!ptr)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		ptr[j++] = line[i++];
	ptr[j] = '\0';
	free (line);
	return (ptr);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*leftover;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!leftover)
	{
		leftover = malloc(1);
		if (!leftover)
			return (NULL);
		leftover[0] = '\0';
	}
	leftover = read_line(fd, leftover);
	if (!leftover)
		return (NULL);
	line = extract_line(leftover);
	leftover = clean_line(leftover);
	return (line);
}

/*
# include <stdio.h>
# include <fcntl.h>
int	main(void)
{
	int	fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR\n");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s",line);
		free (line);
	}
	close (fd);
	return (0);
}
*/