/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:58:37 by plettie           #+#    #+#             */
/*   Updated: 2019/11/07 17:58:38 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char		*parse_env(t_list *env, char *name)
{
	char	**split;

	while (env)
	{
		split = ft_strsplit(env->content, '=');
		if (!ft_strcmp(split[0], name))
		{
			ft_free_split(split);
			return (env->content + ft_strlen(name));
		}
		ft_free_split(split);
		env = env->next;
	}
	return (NULL);
}

static char	*find_path(char *com, t_list *all)
{
	char	*join;
	char	**path;
	int		i;

	path = ft_strsplit(parse_env(all, "PATH"), ':');
	i = -1;
	while (path[++i])
	{
		join = ft_strjoin(ft_strjoin(path[i], "/", 0), com, 1);
		if (!access(join, X_OK))
			return (join);
	}
	return (NULL);
}

void		do_also(char **my_com, t_list *all)
{
	pid_t	pid;

	if (!(pid = fork()))
	{
		if (access(my_com[0], X_OK))
		{
			free(my_com[0]);
			if (!(my_com[0] = find_path(my_com[0], all)))
				ft_putstr("Command is not exists\n");
		}
		execve(my_com[0], my_com, NULL);
	}
	wait(&pid);
}

void		check_vvod(char *com, t_list *all)
{
	char	**my_com;

	if ((my_com = ft_strsplit(com, ' ')) && *my_com)
	{
		if (!(ft_strcmp(my_com[0], "clear")))
			ft_putstr(CLEAR_SCREEN);
		else if (!(ft_strcmp(my_com[0], "cd")))
			do_cd(my_com);
		else if (!(ft_strcmp(my_com[0], "echo")))
			do_echo(my_com, all);
		else if (!(ft_strcmp(my_com[0], "setenv")))
			do_setenv(my_com, all);
		else if (!(ft_strcmp(my_com[0], "unsetenv")))
			do_unsetenv(my_com, all);
		else if (!(ft_strcmp(my_com[0], "env")))
			do_env(all);
		else if (!(ft_strcmp(my_com[0], "exit")))
			exit(0);
		else
			do_also(my_com, all);
	}
}

char		*add_com(char **com, char c)
{
	int		i;
	char	*new_command;
	char	*command;

	command = *com;
	if (!(new_command = malloc(ft_strlen(*com) + 2)))
		return (NULL);
	i = -1;
	while (command[++i])
		new_command[i] = command[i];
	new_command[i++] = c;
	new_command[i] = '\0';
	return (new_command);
}
