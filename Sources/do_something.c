/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:56:06 by plettie           #+#    #+#             */
/*   Updated: 2019/11/13 15:56:07 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_list				*change_oldpwd(t_list *all)
{
	char			*str;
	t_list			*to_del;
	t_list			*lst;
	char			*pwd;

	lst = all;
	if ((to_del = parse_env(all, "OLDPWD")))
	{
		while (all->next != to_del)
			all = all->next;
		all->next = to_del->next;
		free(to_del->content);
		free(to_del);
	}
	if (!(pwd = getcwd(NULL, 0)))
		return (all);
	str = ft_strjoin(ft_strjoin("OLDPWD", "=", 0), pwd, 1);
	lst = list_add_back(all, str);
	free(pwd);
	return (lst);
}

void				do_cd_return(t_list *all)
{
	t_list			*lst;
	char			*src;

	if ((lst = parse_env(all, "OLDPWD")))
	{
		src = ft_strdup(lst->content + 7);
		change_oldpwd(all);
		chdir(src);
		free(src);
	}
}

t_list				*do_cd(char **str, t_list *all)
{
	t_list			*lst;
	char			*src;

	if (kol_args(str) > 2)
		ft_error(3, str[1]);
	if (!(ft_strcmp("-", str[1])))
		do_cd_return(all);
	if (str[1] && ft_strcmp("~", str[1]) && ft_strcmp("-", str[1]))
	{
		all = change_oldpwd(all);
		if (chdir(str[1]))
			ft_error(5, str[1]);
	}
	else if (ft_strcmp("-", str[1]))
	{
		all = change_oldpwd(all);
		if ((lst = parse_env(all, "USER")))
		{
			src = ft_strjoin("/Users/", (lst->content + 5), 0);
			chdir(src);
		}
	}
	return (all);
}

char				*find_path(char *com, t_list *all)
{
	t_list			*path_lst;
	char			**split;
	char			*str;
	int				i;

	if ((path_lst = parse_env(all, "PATH")))
	{
		split = ft_strsplit(path_lst->content + 5, ':');
		i = -1;
		while (split[++i])
		{
			str = ft_strjoin(ft_strjoin(split[i], "/", 0), com, 1);
			if (!access(str, X_OK))
			{
				ft_free_split(split);
				return (str);
			}
			free(str);
		}
		ft_free_split(split);
	}
	return (NULL);
}

int					do_also(char **com, t_list *all, char **env)
{
	pid_t			pid;
	char			*path;

	if (!(pid = fork()))
	{
		if (access(com[0], X_OK))
		{
			if ((path = find_path(com[0], all)))
			{
				free(com[0]);
				com[0] = path;
				free(path);
				execve(com[0], com, env);
			}
			else
			{
				wait(&pid);
				return (ft_error(4, com[0]));
			}
		}
		else
			execve(com[0], com, env);
	}
	wait(&pid);
	return (0);
}
