/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:01:36 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/01/13 10:42:56 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../libft/libft.h"

void	error_msg(char *str);
void	free_paths(char **path);
char	*find_the_path(char **env, char *cmd);
char	*find_in_paths(char **paths, char *cmd);
#endif