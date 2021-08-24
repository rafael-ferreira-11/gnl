/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:00 by raferrei          #+#    #+#             */
/*   Updated: 2021/08/24 10:28:29 by user42           ###   ########.fr       */
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
	static char *overflow;

	#ifdef BUFFER_SIZE
		buffer = BUFFER_SIZE;
	#else
		buffer = 1;
	#endif
	if (fd < 0 || buffer <= 0)
		return (0);
	if (!value)
		value = calloc(buffer, 1);
	ret = malloc(sizeof(char *));
	*ret = 0;
	if(!overflow) {
		overflow = malloc(sizeof(char *));
		*overflow = 0;
	}
	if (!value)
		return (0);

	if (overflow)
	{
		offset = 0;
		while (overflow[offset])
		{
			ret = ft_strjoin(ret, overflow[offset]);
			offset++;
		}
	}
	while (read(fd, value, buffer) > 0)
	{
		index = offset;
		while(index < buffer)
		{
			if (!value[index])
				break;
			ret = ft_strjoin(ret, value[index]);

			if (value[index] == '\n')
			{
				index++;
				while (index < buffer && value[index])
				{
					overflow = ft_strjoin(overflow, value[index]);
					index++;
				}
				return (ret);
			}

			index++;
		}
	}
	if (*ret == 0)
	{
		if(overflow)
			free(overflow);
		free(ret);
		return (0);
	}
	free(overflow);
	free(value);
	return (ret);
}
