/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 09:20:05 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 19:15:53 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 1;
	if (!s)
		return (-2);
	while (s[i] && s[i] != c)
		++i;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			++i;
		while (s[i] && s[i] != c)
		{
			if (s[i - 1] == c)
				++count;
			++i;
		}
	}
	return (count);
}

static int	count_letters(char const *s, char c, int start)
{
	int count;

	count = 0;
	while (s[start] && s[start] != c)
	{
		++count;
		++start;
	}
	return (count);
}

static void	*free_all(char **tab, char **tmp, int *i)
{
	while (*i >= 0)
		ft_strdel(&tab[(*i)--]);
	free(tab);
	ft_strdel(tmp);
	return (NULL);
}

static char	**check_start(char const *s, char c, char **tmp)
{
	char	**tab;
	int		count;

	if (!s)
		return (NULL);
	if (!(*tmp = ft_strctrim(s, c)))
		return (NULL);
	count = count_words(*tmp, c);
	if (!ft_strcmp(s, ""))
		count = 0;
	if ((!(tab = (char **)ft_memalloc((count + 1) * sizeof(*tab)))))
	{
		ft_strdel(tmp);
		return (NULL);
	}
	return (tab);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	char	*tmp;
	int		start;
	int		count;
	int		i;

	tmp = NULL;
	start = 0;
	i = 0;
	if (!(tab = check_start(s, c, &tmp)))
		return (NULL);
	while (tmp[start])
	{
		count = count_letters(tmp, c, start);
		if (!(tab[i] = ft_strsub(tmp, start, count)))
			return (free_all(tab, &tmp, &i));
		++i;
		start += count;
		while (tmp[start] && tmp[start] == c)
			++start;
	}
	tab[i] = NULL;
	ft_strdel(&tmp);
	return (tab);
}
