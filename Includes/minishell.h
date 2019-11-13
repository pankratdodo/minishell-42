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
# include <readline/readline.h>
# include <readline/history.h>

typedef	struct		s_list
{
	struct s_list	*next;
	void			*content;
}					t_list;

void				do_echo(char **str, t_list *all);
int					check_env_echo(char *com, t_list *all);
char				ft_strchr_my(const char *s);

int					do_also(char **com, t_list *all, char **env);
char				*find_path(char *com, t_list *all);
t_list				*do_cd(char **str, t_list *all);
void				do_cd_return(t_list *all);
t_list				*change_oldpwd(t_list *all);

t_list				*add_list_env(char **env);
void				do_env(t_list *all);
t_list				*do_unsetenv(char **com, t_list *all);
t_list				*do_setenv(char **com, t_list *all);
char				*set_with_kov(char *com);

void				check_vvod(char *com, t_list *all, char **env);
int					ft_error(int k, char *str);

void				initialize_readline(void);

t_list				*create_list(void *content);
t_list				*list_add_back(t_list *list, void *content);
t_list				*parse_env(t_list *env, char *name);

char				*ft_strchr(const char *s, int c);
size_t				ft_strlen(const char *src);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_putstr(char const *s);
int					ft_strcmp(const char *s1, const char *s2);
int					kol_args(char **str);
char				**ft_free_split(char **d);
char				*ft_strjoin(char const *s1, char const *s2, int to_free);
char				*ft_strdup(const char *s1);
char				**ft_strsplit(char const *s, char c);

#endif
