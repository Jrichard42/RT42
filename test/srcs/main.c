/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:42:08 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/12 17:37:00 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "thpool.h"

void	toto(void *data)
{
}

int main(int argc, char **argv)
{
	t_thpool *pool;

	pool = create_thpool(10);
	sleep(1);
	push_job(pool, &toto, NULL);
	sleep(1);
}
