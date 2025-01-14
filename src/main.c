/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:01:39 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/01/14 11:03:47 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parse_cmd(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split (argv, ' ');
	if (!cmd)
		error_msg("Memory allocation failed for cmd\n");
	path = find_the_path(env, cmd[0]);
	if (path)
	{
		execve(path, cmd, env);
	}
	free_paths(cmd);
	free(path);
}

void	process1(char *argv[], char **env, int pipefd[2])
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
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

	fd = open(argv[4], O_WRONLY | O_CREAT);
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

int	pipex(char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		stat;

	if (pipe(pipefd) == -1)
		error_msg("the pipe failed.");
	pid1 = fork();
	if (pid1 == 0)
		process1(argv, env, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		process2(argv, env, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &stat, 0);
	waitpid(pid2, &stat, 0);
	return (stat);
}

int	main(int argc, char **argv, char **envp)
{
	int	the_outcome;

	if (argc != 5)
		error_msg("Error\n");
	the_outcome = pipex(argv, envp);
	return (the_outcome);
}
