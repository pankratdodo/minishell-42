/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:46:13 by plettie           #+#    #+#             */
/*   Updated: 2019/11/07 17:46:20 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int			ft_error(int k, char *str)
{
	if (k == 1)
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(str);
		write(1, "\n", 1);
	}
	else if (k == 2)
		ft_putstr("usage : unsetenv [name]\n");
	else if (k == 3)
		ft_putstr("usage : setenv [name] [value]\n");
	else if (k == 4)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(str);
		write(1, "\n", 1);
	}
	else if (k == 5)
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putstr(str);
		write(1, "\n", 1);
	}
	return (0);
}

int			ft_minishell(char *command, t_list *all)
{
	char	c;
	int		i;
	char	**commands;

	command = com_renew(&command, 0);
	write(1, "$> ", 3);
	while (read(1, &c, 1))
	{
		if (c != '\n')
		{
			if (!(command = add_com(&command, c)))
				return (0);
		}
		else
		{
			i = -1;
			commands = ft_strsplit(command, ';');
			while (commands[++i])
				check_vvod(commands[i], all);
			command = com_renew(&command, 1);
			write(1, "$> ", 3);
		}
	}
	return (0);
}

void	my_int(int ret)
{
	write(1, "\n$> ", 4);
	ret = 0;
}

char		*com_renew(char **command, int to_free)
{
	char	*ret;

	if (to_free)
		free(*command);
	if (!(ret = malloc(sizeof(char))))
		return (NULL);
	ret[0] = '\0';
	return (ret);
}

int			main(int ac, char **av, char **env)
{
	char	*command;
	t_list	*all;

	ac = 1;
	*av = NULL;
	all = add_list_env(env);
	command = com_renew(&command, 0);
	signal(SIGINT, my_int);
	return (ft_minishell(command, all));
}
