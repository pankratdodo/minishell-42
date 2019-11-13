/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:16:58 by plettie           #+#    #+#             */
/*   Updated: 2019/11/11 12:16:58 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char			*set_with_kov(char *com)
{
	char		*str;
	int			i;
	int			j;

	str = malloc(sizeof(ft_strlen(com - 2)));
	i = 0;
	j = 0;
	while (com[i] != '\0')
	{
		if (com[i] != '"')
		{
			str[j] = com[i];
			j++;
		}
		i++;
	}
	free(com);
	return (str);
}

t_list			*do_setenv(char **com, t_list *all)
{
	char		*str;
	t_list		*lst;
	t_list		*to_del;

	lst = all;
	if (kol_args(com) != 3)
		ft_error(2, NULL);
	else
	{
		if (ft_strchr(com[2], '"'))
			com[2] = set_with_kov(com[2]);
		if ((to_del = parse_env(all, com[1])))
		{
			while (all->next != to_del)
				all = all->next;
			all->next = to_del->next;
			free(to_del->content);
			free(to_del);
		}
		str = ft_strjoin(ft_strjoin(com[1], "=", 0), com[2], 1);
		lst = list_add_back(all, str);
	}
	return (lst);
}

t_list			*do_unsetenv(char **com, t_list *all)
{
	t_list		*to_del;
	t_list		*lst;

	lst = all;
	if (kol_args(com) != 2)
		ft_error(1, NULL);
	else if ((to_del = parse_env(all, com[1])))
	{
		while (all->next != to_del)
			all = all->next;
		all->next = to_del->next;
		free(to_del->content);
		free(to_del);
	}
	return (lst);
}

void			do_env(t_list *all)
{
	while (all)
	{
		ft_putstr(all->content);
		all = all->next;
		write(1, "\n", 1);
	}
}

t_list			*add_list_env(char **env)
{
	t_list		*head;
	char		*str;
	int			i;

	head = create_list(env[0]);
	i = 0;
	while (env[++i])
	{
		str = ft_strdup(env[i]);
		head = list_add_back(head, str);
	}
	return (head);
}
