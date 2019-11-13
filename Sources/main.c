/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:14:20 by plettie           #+#    #+#             */
/*   Updated: 2019/11/11 12:14:21 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int			ft_error(int k, char *str)
{
	if (k == 1)
		ft_putstr("using: unsetenv [name]\n");
	if (k == 2)
		ft_putstr("using: setenv [name] [value]\n");
	if (k == 3)
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putstr(str);
		write(1, "\n", 1);
	}
	if (k == 4)
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(str);
		write(1, "\n", 1);
	}
	if (k == 5)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(str);
		write(1, "\n", 1);
	}
	return (1);
}

void		my_int(int ret)
{
	ft_putstr("\n$> ");
	ret = 0;
}

void		check_vvod(char *com, t_list *all, char **env)
{
	char	**my_com;

	if ((my_com = ft_strsplit(com, ' ')) && *my_com)
	{
		if (!(ft_strcmp(my_com[0], "clear")))
			ft_putstr(CLEAR_SCREEN);
		else if (!(ft_strcmp(my_com[0], "cd")))
			all = do_cd(my_com, all);
		else if (!(ft_strcmp(my_com[0], "echo")))
			do_echo(my_com, all);
		else if (!(ft_strcmp(my_com[0], "setenv")))
			all = do_setenv(my_com, all);
		else if (!(ft_strcmp(my_com[0], "unsetenv")))
			all = do_unsetenv(my_com, all);
		else if (!(ft_strcmp(my_com[0], "env")))
			do_env(all);
		else if (!(ft_strcmp(my_com[0], "/usr/bin/env")))
			do_env(all);
		else if (!(ft_strcmp(my_com[0], "exit")))
			exit(0);
		else
			do_also(my_com, all, env);
		ft_free_split(my_com);
	}
}

int			main(int ac, char **av, char **env)
{
	char	*command;
	t_list	*all;
	char	**split;
	int		c;

	ac = 1;
	*av = NULL;
	all = add_list_env(env);
	ft_putstr(CLEAR_SCREEN);
	while ((c = -1))
	{
		signal(SIGINT, my_int);
		initialize_readline();
		if (!(command = readline("$> ")))
			return (1);
		add_history(command);
		if (!(split = ft_strsplit(command, ';')))
			return (0);
		while (split[++c])
			check_vvod(split[c], all, env);
		ft_free_split(split);
		free(command);
	}
	return (0);
}
