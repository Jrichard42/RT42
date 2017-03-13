/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:39:32 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/13 16:13:34 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rt.h"
# include "obj.h"
# include "ft_kvlexer.h"
# include "libft_matrix.h"

typedef struct	s_ptr_type
{
	char		type[10];
	int			(*create)(t_kvlexer *token, t_rt *rt);
}				t_ptr_type;

int				parser(char *name, t_rt *rt);
int				search_key(t_list *node, void *data);
t_vector3f		get_as_vector3f(t_kvlexer *token, char *str);
t_vector2f		get_as_vector2f(t_kvlexer *token, char *str);
float			get_as_float(t_kvlexer *token, char *str);
t_material		get_material(t_kvlexer *token);

#endif
