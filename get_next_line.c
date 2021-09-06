/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:00 by raferrei          #+#    #+#             */
/*   Updated: 2021/09/06 17:54:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	read_reserve(int size, char *value, char **ret, int *trigger)
{
	if (*trigger)
	{
		while (*trigger < size && value[*trigger])
		{
			*ret = ft_strjoin(*ret, value[*trigger]);
			if (value[*trigger] == '\n')
			{
				*trigger = *trigger + 1;
				if (!(*trigger < size && value[*trigger]))
					*trigger = 0;
				return (1);
			}
			*trigger = *trigger + 1;
		}
	}
	return (0);
}

char	*check_and_free(char *ret, char *value)
{
	if (*ret == 0)
	{
		free(ret);
		free(value);
		return (0);
	}
	free(value);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*value;
	char		*ret;
	static int	trigger;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	ret = malloc(sizeof(char *));
	if (!ret)
		return (0);
	*ret = 0;
	if (read_reserve(BUFFER_SIZE, value, &ret, &trigger) == 1)
		return (ret);
	trigger = 0;
	value = ft_calloc(BUFFER_SIZE, 1);
	if (!value)
		return (0);
	while (read(fd, value, BUFFER_SIZE) > 0)
	{
		if (read_line(BUFFER_SIZE, value, &ret, &trigger) == 1)
		{
			if(!trigger)
				free(value);
			return (ret);
		}
	}
	return (check_and_free(ret, value));
}
