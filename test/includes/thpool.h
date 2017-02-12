/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:16:10 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/12 17:54:28 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THPOOL_H
# define THPOOL_H

#include "libft.h"


typedef struct		s_job
{
	void			(*do_job)(void *data);
	void			*data;
	struct s_job	*next;
	struct s_job	*head;
	struct s_job	*tail;
}					t_job;

typedef struct		s_thpool
{
	t_job			*job;
}					t_thpool;

t_thpool    	   *create_thpool(int nb);
void				push_job(t_thpool *pool, void (*func)(void *), void *data);
t_job				*pull_job(t_thpool *pool);

#endif
