/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stalash <stalash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:58:33 by stalash           #+#    #+#             */
/*   Updated: 2024/06/15 20:15:48 by stalash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>

int		main(int argc, char **argv, char **envp);
void	pipex(int f1, int f2, char **ag, char **envp);
void	child_process(int f1, int *cmd, char **argv, char **envp);
void	parent_process(int f2, int *cmd, char **argv, char **envp);
void	execute_process(char *argv, char **envp);
char	*path_process(char *cmd, char **envp);
void	free_split(char **split);
void	error(void);

#endif
