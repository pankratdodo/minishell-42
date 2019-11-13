/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:58:21 by wstygg            #+#    #+#             */
/*   Updated: 2019/11/04 14:04:51 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static char	*ft_strrenew(char **s_ptr, const char *new_str, int to_free)
{
	char	*ret;
	int		i;

	i = -1;
	if (!(ret = malloc(ft_strlen(new_str) + 1)))
		return (NULL);
	while (new_str[++i])
		ret[i] = new_str[i];
	ret[i] = '\0';
	if (to_free && s_ptr && *s_ptr)
		free(*s_ptr);
	return (ret);
}

static char	*command_generator(const char *text, int state)
{
	static int	i;
	static int	len;
	char		*name;
	const char	*g_cmd[] = {
			"cd", "echo", "env", "setenv", "unsetenv", "pwd", "exit",
			"emacs", "vim", "mkdir", "ls", "rm", "rmdir", "clear",
			"locate", "touch", "man", "prompt", "less", "colour",
			"mv", "gcc", "cat", (char*)NULL
	};

	if (!state)
	{
		i = 0;
		len = ft_strlen(text);
	}
	while (g_cmd[i] && (name = (char*)g_cmd[i]))
	{
		i++;
		if (ft_strncmp(name, text, len) == 0)
			return (ft_strrenew(NULL, name, 0));
	}
	return ((char *)NULL);
}

static char	**ash_complition(const char *text, int start, int end)
{
	char **matches;

	matches = NULL;
	(void)end;
	if (start == 0)
		matches = rl_completion_matches(text, command_generator);
	return (matches);
}

void		initialize_readline(void)
{
	rl_readline_name = "minishell";
	rl_attempted_completion_function = ash_complition;
}
