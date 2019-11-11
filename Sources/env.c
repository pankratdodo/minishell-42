/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:52:28 by plettie           #+#    #+#             */
/*   Updated: 2019/11/07 17:52:29 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_list		*add_list_env(char **env)
{
	int		i;
	t_list	*con;
	t_list	*ret;

	con = create_list(env[0]);
	con->n = 1;
	ret = con;
	i = 0;
	while (env[++i])
	{
		con = list_add_back(con, env[i]);
		con = con->next;
		con->n = i + 1;
	}
	return (ret);
}

void		do_env(t_list *env)
{
	while (env)
	{
		ft_putstr(env->content);
		env = env->next;
		write(1, "\n", 1);
	}
}

int			do_unsetenv(char **com, t_list *all)
{
	char	**str;
	t_list	*head;

	head = all;
	if (kol_args(com) != 2)
		return (ft_error(2, NULL));
//	while (all)
//	{
//		str = ft_strsplit(all->content, '=');
//		if (ft_strcmp(str[0], com[1]))
//		{
//			ft_free_split(str);
//			all = all->next;
//		}
//		else
//		{
//			ft_free_split(str);
//			list_remove_at(head, all->n, 0);
//			break ;
//		}
//	}
	if (src = parse_env(all, com[1]))
		list_remove_at(head, all->n, 0);
	return (0);
}

int			do_setenv(char **com, t_list *all)
{
	char	**str;
	t_list	*head;

	head = all;
	if (kol_args(com) != 3)
		return (ft_error(3, NULL));
	while (all)
	{
		str = ft_strsplit(all->content, '=');
		if (ft_strcmp(str[0], com[1]))
			all = all->next;
		else
		{
			list_remove_at(head, all->n, 0);
			break ;
		}
	}
	head = list_add_back(head, ft_strjoin(ft_strjoin(com[1], "=", 0),
			com[2], 0));
	all = head;
	return (0);
}
