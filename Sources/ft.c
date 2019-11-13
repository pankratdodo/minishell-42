/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:51:24 by plettie           #+#    #+#             */
/*   Updated: 2019/11/11 12:51:26 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void			ft_putstr(char const *s)
{
	int			index;

	if (!s)
		return ;
	index = 0;
	while (s[index])
	{
		write(1, &s[index], 1);
		index++;
	}
}

int				ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s1 == *s2 && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return ((unsigned char)*s1 - (unsigned char)*s2);
}

char			*ft_strchr(const char *s, int c)
{
	char		*str;
	int			i;
	char		k;

	k = (char)c;
	i = 0;
	while (s[i] != k)
	{
		if (!s[i])
			return (0);
		i++;
	}
	str = (char*)s;
	return (&str[i]);
}

size_t			ft_strlen(const char *src)
{
	size_t		i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}
