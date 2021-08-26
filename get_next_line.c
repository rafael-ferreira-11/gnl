/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:00 by raferrei          #+#    #+#             */
/*   Updated: 2021/08/26 11:16:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*value;
	char		*ret;
	int			index;
	static int	trigger;

	ret = malloc(sizeof(char *));
	*ret = 0;
	if (!ret || fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (trigger)
	{
		while (trigger < BUFFER_SIZE && value[trigger])
		{
			ret = ft_strjoin(ret, value[trigger]);
			if (value[trigger] == '\n')
			{
				trigger++;
				if (!(trigger < BUFFER_SIZE && value[trigger]))
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
		index = 0;
		while (index < BUFFER_SIZE && value[index])
		{
			ret = ft_strjoin(ret, value[index]);
			if (value[index] == '\n')
			{
				index++;
				if (index < BUFFER_SIZE && value[index])
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
