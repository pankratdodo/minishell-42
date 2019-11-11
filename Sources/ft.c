/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:28:01 by plettie           #+#    #+#             */
/*   Updated: 2019/10/12 18:28:05 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char				*ft_strjoin(char const *s1, char const *s2, int to_free)
{
	char			*str;
	size_t			i;
	size_t			k;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char*)malloc(ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1)))
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i])
		str[k++] = s1[i++];
	i = 0;
	while (s2[i])
		str[k++] = s2[i++];
	str[k] = '\0';
	(to_free == 1) ? free((void*)s1) : 0;
	(to_free == 2) ? free((void*)s2) : 0;
	return (str);
}

void				ft_putstr(char const *s)
{
	int				index;

	if (!s)
		return ;
	index = 0;
	while (s[index])
	{
		write(1, &s[index], 1);
		index++;
	}
}

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

int					ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str;
	unsigned char	*src;

	str = (unsigned char *)s1;
	src = (unsigned char *)s2;
	while (*str == *src && *str)
	{
		str++;
		src++;
	}
	return (*str - *src);
}

size_t				ft_strlen(const char *s)
{
	size_t			i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
