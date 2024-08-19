/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:17:28 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/19 22:36:56 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
/*gnl*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/*printf*/
# include <stdarg.h>

/*pritf*/
# define LHEX "0123456789abcdef"
# define UHEX "0123456789ABCDEF"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *h, const char *n, size_t len);
int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *str, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	ft_error_print(void);

void	clear_array(char **array);

/**
 * printf
 */
ssize_t	ft_ssize_putchar_fd(char c, int fd);
int		ft_print_format(const char *format, va_list *ap);
int		ft_print_str(char *str);
int		ft_print_number(int num);
int		ft_print_unsigned_number(unsigned int num);
int		ft_print_hex(unsigned int num, const char conversion);
int		ft_print_pointer(unsigned long int ptr);
int		ft_printf(const char *format, ...);

/*gnl*/
char	*get_next_line(int fd);
char	*ft_gnl_free(char **str);
char	*ft_gnl_strjoin(char *s1, char *s2);
size_t	ft_gnl_strlen(char *s);
char	*ft_gnl_strchr(char *s, int c);
char	*ft_gnl_substr(char *s, size_t start, size_t len);

#endif
