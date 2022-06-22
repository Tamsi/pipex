/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsibesson <tamsibesson@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:37:34 by tamsibesson       #+#    #+#             */
/*   Updated: 2022/06/22 12:39:21 by tamsibesson      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freetab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**get_path(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			break ;
		i++;
	}
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*cmd_path;
	char	*add_slash;
	char	**path;

	i = 0;
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	path = get_path(envp);
	while (path[i])
	{
		add_slash = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(add_slash, cmd);
		free(add_slash);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	freetab(path);
	return (NULL);
}
