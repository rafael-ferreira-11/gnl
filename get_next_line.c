/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:00 by raferrei          #+#    #+#             */
/*   Updated: 2021/08/25 09:43:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*(s++) != '\0')
		length++;
	return (length);
}

char	*ft_strjoin(char *s1, char s2)
{
	char	*res;
	int		i;

	if (!s1 || !s2)
		return (0);
	res = (char *)malloc(ft_strlen(s1) + 1 + 1);
	if (!res)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = s2;
	i++;
	res[i] = '\0';
	free(s1);
	return (res);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		((unsigned char *)s)[index] = c;
		index++;
	}
	return (s);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*res;

	res = malloc(num * size);
	if (!res)
		return (0);
	ft_memset(res, 0, num * size);
	return (res);
}

char *get_next_line(int fd)
{
	int buffer;
	static char *value;
	char *ret;
	int	index;
	int offset;
	static int trigger;

	#ifdef BUFFER_SIZE
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
		while (trigger < buffer)
		{
			ret = ft_strjoin(ret, value[trigger]);
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
		if(offset)
		{
		index = offset;
		offset = 0;
		}
		else
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
	}
	if (*ret == 0)
	{
		free(ret);
		return (0);
	}
	free(value);
	return (ret);
}
