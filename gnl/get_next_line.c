/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjanulek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 08:12:00 by mjanulek          #+#    #+#             */
/*   Updated: 2020/09/01 08:12:00 by mjanulek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int				gnl_strcpy(char *src, char *dest, int mode)
{
	int					i;

	i = 0;
	if (mode == 1)
	{
		while (*src && *src != '\n')
		{
			*dest++ = *src++;
			i++;
		}
	}
	else
	{
		while (*src)
		{
			*dest++ = *src++;
			i++;
		}
	}
	*dest = 0;
	return (i);
}

static char				*gnl_append(char **line, char *str)
{
	int					len;
	char				*temp;
	char				*ptr;

	len = gnl_strlen(*line) + gnl_strlen(str) + 1;
	if (!(temp = malloc(sizeof(char) * (gnl_strlen(*line) + 1))))
		return (NULL);
	gnl_strcpy(*line, temp, 1);
	free(*line);
	if (!(*line = malloc(sizeof(char) * len)))
		return (NULL);
	len = gnl_strcpy(temp, *line, 1);
	free(temp);
	len = gnl_strcpy(str, (*line) + len, 1);
	ptr = str + len;
	return (ptr);
}

static void				gnl_get_buffer(t_buffer *buffer, int fd, int *rst)
{
	if (!(((buffer->buffer)[fd][0])))
	{
		gnl_bzero((buffer->buffer)[fd], BUFFER_SIZE + 1);
		*rst = read(fd, (buffer->buffer)[fd], BUFFER_SIZE);
	}
}

static int				gnl_read(t_buffer *buffer, char **line, int fd)
{
	int					rst;
	char				*ptr;

	rst = BUFFER_SIZE;
	while (rst == BUFFER_SIZE)
	{
		if (!(((buffer->buffer)[fd][0])))
			gnl_get_buffer(buffer, fd, &rst);
		if ((buffer->buffer)[fd][0])
		{
			if (!(ptr = gnl_append(line, (buffer->buffer)[fd])))
				return (-1);
			if (*ptr == '\n')
			{
				gnl_strcpy(ptr + 1, (buffer->buffer)[fd], 0);
				return (1);
			}
			else
				gnl_strcpy(ptr, (buffer->buffer)[fd], 0);
		}
	}
	return (gnl_decide(rst, *line));
}

int						get_next_line(int fd, char **line)
{
	static int			init = 0;
	static t_buffer		buffer;
	char				temp[1];

	if (!line || fd < 0 || BUFFER_SIZE < 1 || fd >= OPEN_MAX ||
	read(fd, &temp, 0) < 0)
		return (-1);
	*line = malloc(sizeof(char));
	**line = 0;
	if (init == 0)
	{
		gnl_init(&buffer);
		init = 1;
	}
	return (gnl_read(&buffer, line, fd));
}
