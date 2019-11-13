/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:15:20 by plettie           #+#    #+#             */
/*   Updated: 2019/11/11 13:15:21 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char				*ft_strdup(const char *s1)
{
	int				i;
	char			*str;

	i = 0;
	while (s1[i])
		i++;
	str = (char*)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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

char				**ft_free_split(char **d)
{
	int				i;

	i = 0;
	while (d[i])
	{
		free(d[i]);
		i++;
	}
	free(d);
	return (NULL);
}

int					kol_args(char **str)
{
	int				i;

	i = 1;
	while (str[i])
		i++;
	return (i);
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
