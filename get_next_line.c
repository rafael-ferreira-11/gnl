/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <ferreira@asia.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 12:16:00 by raferrei          #+#    #+#             */
/*   Updated: 2021/08/17 10:25:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char    *get_next_line(int fd)
{
    int index;
    int buffer;
    char *ret;

    index = 0;

    #ifdef  BUFFER_SIZE
        buffer = BUFFER_SIZE;
    #else
        buffer = 128;
    #endif
	ret = malloc(buffer);
    if(!ret)
        return ("");
    while (read(fd, &ret[index], 1) != 0 && ret[index] != '\n') 
        index++;
        
    if (index == 0)
        return (malloc(1));
    return (ret);
}