/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 22:34:41 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/18 23:26:23 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <sys/stat.h>
       #include <fcntl.h>

#include "libft.h"
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int	fd = open(argv[1], O_RDONLY);
	char *line;

	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
printf("line = %s\n", line);
	}
}
