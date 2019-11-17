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

void				do_cd_sign(char *str, t_list *all)
{
	t_list			*lst;
	char			*src;

	if ((lst = parse_env(all, "HOME")))
	{
		if (str[1])
			src = ft_strjoin(lst->content + 5, str + 1, 0);
		else
			src = ft_strdup(lst->content + 5);
		all = change_oldpwd(all);
		chdir(src);
		free(src);
	}
}

void				do_cd_without(t_list *all)
{
	t_list			*lst;
	char			*src;

	if ((lst = parse_env(all, "HOME")))
	{
		src = ft_strdup(lst->content + 5);
		all = change_oldpwd(all);
		chdir(src);
		free(src);
	}
}

t_list				*do_cd(char **str, t_list *all)
{
	if (kol_args(str) > 2)
		ft_error(3, str[1]);
	if (str[1] && !(ft_strcmp("-", str[1])))
		do_cd_return(all);
	else if (str[1] && str[1][0] == '~')
		do_cd_sign(str[1], all);
	else if (str[1] && ft_strcmp("~", str[1]) && ft_strcmp("-", str[1]))
	{
		all = change_oldpwd(all);
		if (chdir(str[1]))
			ft_error(5, str[1]);
	}
	else
		do_cd_without(all);
	return (all);
}
