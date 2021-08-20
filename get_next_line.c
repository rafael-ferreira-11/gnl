/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:00 by raferrei          #+#    #+#             */
/*   Updated: 2021/08/20 11:54:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	int index;
	int buffer;
	char *ret;

	index = 0;

	#ifdef BUFFER_SIZE
		buffer = BUFFER_SIZE;
	#else
		buffer = 1;
	#endif
	if (fd < 0 || buffer <= 0)
		return (0);
	ret = malloc(sizeof (char *));
	if (!ret)
		return (0);
	while (read(fd, &ret[index], buffer) > 0 && ret[index] != '\n')
	{
	index++;
	}


	if (index == 0 && ret[0] == 0)
	{
		free(ret);
		return (0);
	}
	return (ret);
}
