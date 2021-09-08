/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 09:40:51 by user42            #+#    #+#             */
/*   Updated: 2021/09/08 09:42:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (dst == src)
		return (dst);
	if (s < d)
	{
		while (len--)
			*(d + len) = *(s + len);
		return (dst);
	}
	while (len--)
		*d++ = *s++;
	return (dst);
}

char	*join_str(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	rtn_len;
	char	*rtn;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	rtn_len = s1_len + s2_len + 1;
	rtn = malloc(sizeof(char) * rtn_len);
	if (!rtn)
		return (0);
	ft_memmove(rtn, s1, s1_len);
	ft_memmove(rtn + s1_len, s2, s2_len);
	rtn[rtn_len - 1] = '\0';
	free((char *)s1);
	return (rtn);
}

int	check_return(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
