/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:21:40 by plettie           #+#    #+#             */
/*   Updated: 2019/10/13 20:21:42 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MINISHELL_H
# define MINISHELL_MINISHELL_H
# define CLEAR_SCREEN "\033[?1049h\033[H"

# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

typedef	struct		s_list
{
	struct s_list	*next;
	void			*content;
	int				n;
}					t_list;

int					do_setenv(char **com, t_list *all);
int					do_unsetenv(char **com, t_list *all);
void				do_cd(char **str);
void				do_echo(char **str, t_list *all);
void				do_env(t_list *env);
void				do_also(char **my_com, t_list *all);

t_list				*add_list_env(char **env);
char				*com_renew(char **command, int to_free);
int					ft_minishell(char *command, t_list *all);
void				check_vvod(char *com, t_list *all);
char				*add_com(char **com, char c);
int					ft_error(int k, char *str);
t_list				*create_list(void *content);
t_list				*list_add_back(t_list *list, void *content);
t_list				*list_remove_at(t_list *lst, int at, int to_free);
char				*parse_env(t_list *env, char *name);

size_t				ft_strlen(const char *s);
char				**ft_strsplit(char const *s, char c);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_putstr(char const *s);
int					kol_args(char **str);
char				ft_strchr_my(const char *s);
char				*ft_strjoin(char const *s1, char const *s2, int to_free);
int					ft_free_str(char *str);
char				**ft_free_split(char **d);

#endif //MINISHELL_MINISHELL_H
