/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:01:39 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/01/07 11:03:07 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	process1(char *argv[], char **env, int pipefd[2])
{
	int	fd;

	fd = open(argv[1], 0);
	if (fd == -1)
		error_msg("Error opening infile\n");
	else if (dup2(fd, STDIN_FILENO) == -1)
		error_msg("dup2() Error on stdin of infile\n");
	else if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_msg("dup2() Error on stdout of infile\n");
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
	parse_cmd(argv[2], env);
}

void	process2(char **argv, char **env, int pipefd[2])
{
	int	fd;

	fd = open(argv[4], 1);
	if (fd == -1)
		error_msg("Error opening outfile\n");
	else if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_msg("dup2() Error on stdin of outfile\n");
	else if (dup2(fd, STDOUT_FILENO) == -1)
		error_msg("dup2() Error on stdout of outfile\n");
	close (pipefd[0]);
	close (pipefd[1]);
	close (fd);
	parse_cmd(argv[3], env);
}

void	parse_cmd(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split (argv, ' ');
	path = find_the_path(cmd[0], env);
	if (!path)
	{
		free_paths(cmd);
		error_msg("Error, Couldn't find path\n");
	}
	if (execve(path, cmd, env) == -1)
		error_msg("execve failed\n");
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		error_msg("Error\n");

	return (0);
}
