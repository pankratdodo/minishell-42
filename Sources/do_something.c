/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:11:04 by plettie           #+#    #+#             */
/*   Updated: 2019/11/07 18:11:07 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int			ft_free_str(char *str)
{
	free(str);
	str = NULL;
	return (0);
}

int			kol_args(char **str)
{
	int		i;

	i = 1;
	while (str[i])
		i++;
	return (i);
}

void		do_cd(char **str)
{
	if (kol_args(str) > 2)
		ft_error(5, str[0]);
	if (str[1] && ft_strcmp("~", str[1]))
	{
		if (chdir(str[1]))
			ft_error(4, str[1]);
	}
	else
		chdir("/Users/plettie");
}

int			check_env_echo(char *com, t_list *all)
{
	char	**str;

	if (com[0] == '$')
	{
		while (all)
		{
			str = ft_strsplit(all->content, '=');
			if (ft_strcmp(str[0], &com[1]))
			{
				ft_free_split(str);
				all = all->next;
			}
			else
			{
				ft_free_split(str);
				ft_putstr(all->content + ft_strlen(com));
				return (1);
			}
		}
	}
	return (1);
}

void		do_echo(char **str, t_list *all)
{
	int		i;
	char	c;
	int		j;

	i = 1;
	c = 0;
	while (str[i] && (j = -1))
	{
		if (!check_env_echo(str[i], all))
		{
			if (!c)
				c = ft_strchr_my(str[i]);
			while (str[i][++j])
				if (str[i][j] != c)
					write(1, str[i] + j, 1);
		}
		if (str[++i])
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}
