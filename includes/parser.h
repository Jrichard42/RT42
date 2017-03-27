/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:39:32 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/27 16:22:16 by jrichard         ###   ########.fr       */
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
int				error_parser(char *str, char *type);
int				parser_text_mat(t_kvlexer *token, t_rt *rt);
int				search_key(t_list *node, void *data);
int				get_as_vector3f(t_kvlexer *token, char *str, t_vector3f *vec);
int				get_as_vector2f(t_kvlexer *token, char *str, t_vector2f *vec);
int				get_as_float(t_kvlexer *token, char *str, float *f);
int				get_as_double(t_kvlexer *token, char *str, double *d);
int				get_as_int(t_kvlexer *token, char *str, int *i);
int				get_as_string(t_kvlexer *token, char *str, char **string);
int				get_material(t_kvlexer *token, t_rt *rt, t_material *mat);
int				get_texture(t_kvlexer *token, t_rt *rt, t_texture *tex);
t_light			get_light(t_kvlexer *token);

#endif
