/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:24:51 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/06 11:49:50 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_MANAGER_H
# define THREAD_MANAGER_H

# include <pthread.h>
# include "rt.h"

typedef struct			s_thread_data
{
	int					index;
	int					size;
	t_rt				*rt;
}						t_thread_data;

void					thread_manager(t_rt *rt);

#endif
