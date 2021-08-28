/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:12 by raferrei          #+#    #+#             */
/*   Updated: 2021/08/28 11:29:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	index;

	if (!s)
		return (0);
	if ((size_t)start > ft_strlen(s))
		return (0);
	if (ft_strlen(s) - start > len)
		res = (char *)malloc(len + 1);
	else
		res = (char *)malloc(ft_strlen(s) - start + 1);
	if (!res)
		return (0);
	index = 0;
	while (index < len)
	{
		res[index] = s[start + index];
		index++;
	}
	res[index] = 0;
	return (res);
}
