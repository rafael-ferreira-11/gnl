/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:00 by raferrei          #+#    #+#             */
/*   Updated: 2021/08/28 14:12:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	read_line(int size, char *value, char **ret, int *trigger)
{
	int	index;

	index = 0;
	while (index < size && value[index])
	{
		*ret = ft_strjoin(*ret, value[index]);
		if (value[index] == '\n')
		{
			if (index++ < size && value[index])
				*trigger = index;
			return (1);
		}
		index++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*value;
	char		*ret;
	static int	trigger;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	ret = malloc(sizeof(char *));
	*ret = 0;
	if (!ret)
		return (0);
	if (trigger)
	{
		while (trigger < BUFFER_SIZE && value[trigger])
		{
			ret = ft_strjoin(ret, value[trigger]);
			if (value[trigger] == '\n')
			{
				if (!(trigger++ < BUFFER_SIZE && value[trigger]))
					trigger = 0;
				return (ret);
			}
			trigger++;
		}
		trigger = 0;
	}
	value = calloc(BUFFER_SIZE, 1);
	if (!value)
		return (0);
	while (read(fd, value, BUFFER_SIZE) > 0)
	{
		if (read_line(BUFFER_SIZE, value, &ret, &trigger) == 1)
			return (ret);
		free(value);
		value = calloc(BUFFER_SIZE, 1);
	}
	if (*ret == 0)
	{
		free(ret);
		return (0);
	}
	free(value);
	return (ret);
}
