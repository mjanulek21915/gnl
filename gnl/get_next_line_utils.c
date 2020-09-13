/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjanulek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 08:12:00 by mjanulek          #+#    #+#             */
/*   Updated: 2020/09/01 08:12:00 by mjanulek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void				gnl_bzero(char *str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		str[i] = 0;
		i++;
	}
}

int					gnl_init(t_buffer *buffer)
{
	int i;

	i = 0;
	while (i < OPEN_MAX)
		gnl_bzero(((buffer->buffer)[i++]), BUFFER_SIZE + 1);
	return (0);
}

int					gnl_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int					gnl_decide(int i, char *line)
{
	if (i == 0 && !*line)
		return (0);
	if (i == -1)
		return (-1);
	else
		return (1);
}
