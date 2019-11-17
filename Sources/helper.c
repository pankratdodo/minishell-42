/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 23:33:00 by plettie           #+#    #+#             */
/*   Updated: 2019/11/13 23:33:01 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int				do_also(char **com, t_list *all, char **env)
{
	pid_t		pid;
	char		*path;

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

char			*find_path(char *com, t_list *all)
{
	t_list		*path_lst;
	char		**split;
	char		*str;
	int			i;

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

t_list			*list_add_back(t_list *list, void *content)
{
	t_list		*item;
	t_list		*ret;

	if (!list)
		return (create_list(content));
	ret = list;
	while (list->next)
		list = list->next;
	if (!(item = malloc(sizeof(t_list))))
	{
		write(1, "Malloc error\n", 13);
		exit(1);
	}
	item->content = content;
	item->next = NULL;
	list->next = item;
	return (ret);
}

t_list			*create_list(void *content)
{
	t_list		*ret;

	if (!(ret = malloc(sizeof(t_list))))
	{
		write(1, "Malloc error\n", 13);
		exit(1);
	}
	ret->content = content;
	ret->next = NULL;
	return (ret);
}

t_list			*parse_env(t_list *env, char *name)
{
	char		**split;

	while (env)
	{
		split = ft_strsplit(env->content, '=');
		if (!ft_strcmp(split[0], name))
		{
			ft_free_split(split);
			return (env);
		}
		ft_free_split(split);
		env = env->next;
	}
	return (NULL);
}
