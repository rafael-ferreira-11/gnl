/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:00 by raferrei          #+#    #+#             */
/*   Updated: 2021/08/28 11:04:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*copy_reserve(int *tr, int size, char *value, char *r)
{
	int	t;

	t = *tr;
	while (t < size && value[t])
	{
		r = ft_strjoin(r, value[t]);
		if (value[t] == '\n')
		{
			if (!(t++ < size && value[t]))
				t = 0;
			return (r);
		}
		t++;
	}
	return (r);
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
		ret = copy_reserve(&trigger, BUFFER_SIZE, value, ret);
		if (*ret == '\n')
			return (ret);
		trigger = 0;
	}
	value = calloc(BUFFER_SIZE, 1);
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
