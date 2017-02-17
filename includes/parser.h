/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:39:32 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/17 19:54:49 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_kvlexer.h"
# include "raytracer.h"

typedef struct	s_ptr_type
{
	char		type[10];
	int			(*create)(t_kvlexer *token, t_raytracer *raytracer);
}				t_ptr_type;

int				parser(char *name, t_raytracer *raytracer);

#endif
