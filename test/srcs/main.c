/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:42:08 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/13 11:34:18 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "thpool.h"

void	toto(void *data)
{
	printf("doing stuff\n");
}

int main(int argc, char **argv)
{
	t_thpool *pool;

	pool = create_thpool(2, 10, 0);
	usleep(100);
	push_job(pool, &toto, NULL);
	usleep(100);
}
