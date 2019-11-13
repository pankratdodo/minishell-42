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
