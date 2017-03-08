/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 09:47:23 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/18 22:35:14 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define BUFF_SIZE 4096

typedef struct	s_gnldata
{
	int		fd;
	int		index;
	char	*buff;
}				t_gnldata;

int				get_next_line(const int fd, char **line);
void			delgnl(void *content, size_t content_size);

#endif
