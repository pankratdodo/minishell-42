/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:48:27 by plettie           #+#    #+#             */
/*   Updated: 2019/04/15 13:24:46 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int		ft_s(char *str, char c)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
	if (str[i] == c)
	{
		while (str[i] == c)
			i++;
	}
	if (!str[i])
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i - 1] != c)
			k++;
		i++;
	}
	if (str[i] == '\0' && str[i - 1] != c)
		k++;
	return (k);
}

static char		*ft_mem(char *s, int m)
{
	char		*str;
	int			i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (m + 1))))
		return (0);
	while (m > i)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int		ft_size(char *str, char c)
{
	int			m;
	int			i;

	i = 0;
	m = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c)
			m++;
		if (str[i] == c && str[i - 1] != c)
			return (m);
		i++;
	}
	return (m);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**s1;
	int			i;
	int			j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	if (!(s1 = (char **)malloc(sizeof(char*) * ((ft_s((char *)(s), c)) + 1))))
		return (0);
	while (j < (ft_s((char *)(s), c)))
	{
		if (s[i] != c)
		{
			if (!(s1[j] = ft_mem((char*)(&s[i]), ft_size((char*)&s[i], c))))
				return (ft_free_split(&s1[j]));
			j++;
			i += ft_size((char*)&s[i], c);
		}
		i++;
	}
	s1[j] = NULL;
	return (s1);
}
