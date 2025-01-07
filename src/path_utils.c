/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:32:57 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/01/05 07:47:49 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void	free_paths(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

char	**split_the_paths(char **env, char *start)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			start = ft_substr(env[i], 5, ft_strlen(env[i]));
			paths = ft_split(start, ':');
			free (start);
		}
		i++;
	}
	return (paths);
}

char	*find_the_path(char **env, char *cmd)
{
	char	**paths;
	char	*path;
	char	*shortpath;
	int		i;

	i = 0;
	while (paths[i])
	{
		shortpath = ft_strjoin(paths[i], "/");
		path = ft_strjoin(shortpath, cmd);
		free(shortpath);
		if (access(path, F_OK) == 0)
		{
			free_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}
