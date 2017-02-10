/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:45:33 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 19:42:43 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

# define ABS(Value) Value < 0 ? -Value : Value
# define MAX(a, b) a > b ? a : b
# define MIN(a, b) a > b ? b : a

typedef struct	s_list
{
	size_t			content_size;
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct	s_dlist
{
	t_list		*head;
	t_list		*tail;
}				t_dlist;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *restrict dst, const void *restrict src,
							size_t n);
void			*ft_memccpy(void *restrict dst, const void *restrict src,
							int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char	*restrict s1, const char *restrict s2);
char			*ft_strncat(char *restrict s1, const char *restrict s2,
							size_t n);
size_t			ft_strlcat(char *restrict dst, const char *restrict src,
							size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
double			ft_atof(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_isblank(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			*ft_strctrim(char const *s, char c);
char			**ft_strsplit(char const *s, char c);
void			*ft_realloc(void *ptr, size_t size);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_dlist **alst, t_list *current,
								void (*del)(void*, size_t));
void			ft_lstdel(t_dlist **alst, void (*del)(void *, size_t));
int				ft_lstadd(t_dlist **alst, t_list *new);
int				ft_lstadd_end(t_dlist **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
int				ft_lstcheck(t_list *lst, int (*f)(t_list *elem));
t_dlist			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstsearch(t_list *lst, int (*f)(t_list *elem, void *data),
								void *data);
int				ft_lstsize(t_list *lst);
void			*ft_error(char *s);

#endif
