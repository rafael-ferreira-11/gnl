/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:06:10 by user42            #+#    #+#             */
/*   Updated: 2021/09/09 09:13:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_reserve(char *reserve)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!reserve)
		return (0);
	while (reserve[i] && reserve[i] != '\n')
		i++;
	if (!reserve[i])
	{
		free(reserve);
		return (0);
	}
	rtn = malloc(sizeof(char) * ((ft_strlen(reserve) - i) + 1));
	if (!rtn)
		return (0);
	i++;
	while (reserve[i])
		rtn[j++] = reserve[i++];
	rtn[j] = '\0';
	free(reserve);
	return (rtn);
}

char	*get_line(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	rtn = malloc(sizeof(char) * (i + 2));
	if (!rtn)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rtn[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		rtn[i] = '\n';
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char	*get_end(char *line, int reader)
{
	if (reader == 0)
	{
		if (line[0])
			return (line);
		free(line);
		return (0);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char			*buff;
	static char		*reserve;
	char			*line;
	int				reader;

	reader = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	while (!check_return(reserve) && reader != 0)
	{
		reader = read(fd, buff, BUFFER_SIZE);
		if (reader == -1)
			break ;
		buff[reader] = '\0';
		reserve = join_str(reserve, buff);
	}
	free(buff);
	line = get_line(reserve);
	reserve = get_reserve(reserve);
	return (get_end(line, reader));
}
