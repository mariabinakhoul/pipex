/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:32:57 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/01/14 11:00:49 by mabi-nak         ###   ########.fr       */
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

	if (!path)
		return ;
	i = 0;
	while (path && path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

char	*find_in_paths(char **paths, char *cmd)
{
	char	*tmp_path;
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		if (!tmp_path)
			return (NULL);
		path = ft_strjoin(tmp_path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	if (paths)
		free(paths);
	return (NULL);
}

char	*find_the_path(char **env, char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	path = find_in_paths(paths, cmd);
	return (path);
}
