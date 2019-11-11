/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:53:15 by wstygg            #+#    #+#             */
/*   Updated: 2019/10/27 13:58:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char		**ft_free_split(char **d)
{
	int		i;

	i = 0;
	while (d[i])
	{
		free(d[i]);
		i++;
	}
	free(d);
	return (NULL);
}

t_list			*list_at(t_list *lst, int at)
{
	t_list		*ret;
	int			i;

	if (!lst)
		return (NULL);
	if ((i = 1) && at <= 0)
		return (lst);
	ret = lst;
	while (lst->next && i < at)
	{
		lst = lst->next;
		i++;
	}
	if (i == at)
		return (lst);
	return (ret);
}

t_list			*list_remove_at(t_list *lst, int at, int to_free)
{
	t_list		*lst_at;
	t_list		*lst_before;

	if (!(lst_at = list_at(lst, at)))
		return (NULL);
	if (lst_at == lst && at != 1)
		return (lst);
	if (at == 1)
	{
		lst = lst->next;
		if (to_free)
			free(lst->content);
		free(lst);
	}
	else
	{
		lst_before = list_at(lst, at - 1);
		lst_before->next = lst_at->next;
		if (to_free)
			free(lst_at->content);
		free(lst_at);
	}
	return (lst);
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
