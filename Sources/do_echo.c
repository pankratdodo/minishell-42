/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:44:12 by plettie           #+#    #+#             */
/*   Updated: 2019/11/13 15:44:14 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char				ft_strchr_my(const char *s)
{
	int				i;
	char			c;

	i = 0;
	while (s[i] != 34 && s[i] != 39)
	{
		if (!s[i])
			return (0);
		i++;
	}
	c = s[i];
	return (c);
}

int					check_env_echo(char *com, t_list *all)
{
	t_list			*str;

	if (com[0] == '$')
	{
		if ((str = parse_env(all, &com[1])))
			ft_putstr(str->content + ft_strlen(com));
		return (1);
	}
	return (0);
}

void				do_echo(char **str, t_list *all)
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
