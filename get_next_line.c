/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:00 by raferrei          #+#    #+#             */
/*   Updated: 2021/08/26 10:38:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			buffer;
	static char	*value;
	char 		*ret;
	int			index;
	int 		offset;
	static int	trigger;

	#ifdef BUFFER_SIZE && BUFFER_SIZE > 0
		buffer = BUFFER_SIZE;
	#else
		buffer = 1;
	#endif
	if (fd < 0 || buffer <= 0)
		return (0);
	ret = malloc(sizeof(char *));
	*ret = 0;
	if (!ret)
		return (0);
	offset = 0;
	if (trigger)
	{
		while (trigger < buffer && value[trigger])
		{
			ret = ft_strjoin(ret, value[trigger]);
			if (value[trigger] == '\n')
			{
				trigger++;
				if(!(trigger < buffer && value[trigger]))
					trigger = 0;
				return (ret);
			}
			trigger++;
			offset++;
		}
		trigger = 0;
	}
	value = calloc(buffer, 1);
	if(!value)
		return (0);
	while (read(fd, value, buffer) > 0)
	{
			index = 0;
		while(index < buffer && value[index])
		{
			ret = ft_strjoin(ret, value[index]);
			if (value[index] == '\n')
			{
				index++;
				if(index < buffer && value[index])
					trigger = index;
				return (ret);
			}
			index++;
		}
		free(value);
		value = calloc(buffer,1);
	}
	if (*ret == 0)
	{
		free(ret);
		return (0);
	}
	free(value);
	return (ret);
}
