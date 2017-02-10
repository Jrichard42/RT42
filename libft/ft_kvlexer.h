/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvlexer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:12:35 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 14:06:04 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_KVLEXER_H
# define FT_KVLEXER_H

#include "libft.h"

typedef struct		s_kvlexer
{
	int				nb;
	char			*key;
	char			*value;
	struct s_kvlexer	*father;
	t_dlist			*children;
}					t_kvlexer;

t_kvlexer       *ft_kvlexer(char *name);
void		*free_kvlexer(t_kvlexer *kvlexer);

#endif
