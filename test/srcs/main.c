/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:42:08 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/13 17:07:07 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "thpool.h"

void	toto(void *data)
{
	printf("bla\n");
}

int main(int argc, char **argv)
{
	t_thpool *pool;

	pool = create_thpool(1, 100000, sizeof(char *) * 5);
	for(int i = 0;i < 10;++i)
	{
		push_job(pool, &toto, NULL);
	}
}
