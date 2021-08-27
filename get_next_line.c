/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:00 by raferrei          #+#    #+#             */
/*   Updated: 2021/08/27 11:51:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_reserve(int index, int size, char *value)
{
	char	*res;

	res = malloc(sizeof(char *));
	*res = 0;

	while (index < size && value[index])
		{
			res = ft_strjoin(res, value[index]);
			if (value[index] == '\n')
			{
				if (!(index++ < size && value[index]))
					index = 0;
				return (res);
			}
			index++;
		}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*value;
	char		*ret;
	int			index;
	static int	trigger;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	ret = malloc(sizeof(char *));
	*ret = 0;
	if (!ret)
		return (0);
	if (trigger)
	{
		ret = get_reserve(trigger, BUFFER_SIZE, value);
		if (*ret == '\n')
			return (ret);
		trigger = 0;
	}
	value = calloc(BUFFER_SIZE, 1);
	if (!value)
		return (0);
	while (read(fd, value, BUFFER_SIZE) > 0)
	{
		index = 0;
		while (index < BUFFER_SIZE && value[index])
		{
			ret = ft_strjoin(ret, value[index]);
			if (value[index] == '\n')
			{
				if (index++ < BUFFER_SIZE && value[index])
					trigger = index;
				return (ret);
			}
			index++;
		}
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
