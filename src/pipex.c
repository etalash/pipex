/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stalash <stalash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:31:54 by stalash           #+#    #+#             */
/*   Updated: 2024/05/29 20:33:06 by stalash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_process(char *argv, char **envp)
{
	char	**cmd;
	char	*find_path;

	cmd = ft_split(argv, ' ');
	find_path = path_process(cmd[0], envp);
	if (!find_path)
	{
		free_split(cmd);
		error();
	}
	if (execve(find_path, cmd, envp) == -1)
	{
		perror("execve");
		free(find_path);
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	free(find_path);
	free_split(cmd);
}

void	parent_process(int f2, int *cmd, char **argv, char **envp)
{
	if (dup2(f2, STDOUT_FILENO) == -1 || dup2(cmd[0], STDIN_FILENO) == -1)
	{
		perror("dup2: ");
		close(cmd[1]);
		close(f2);
		close(cmd[0]);
		exit(EXIT_FAILURE);
	}
	close(cmd[1]);
	close(f2);
	close(cmd[0]);
	execute_process(argv[3], envp);
	exit(EXIT_SUCCESS);
}

void	child_process(int f1, int *cmd, char **argv, char **envp)
{
	if (dup2(f1, STDIN_FILENO) == -1 || dup2(cmd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2: ");
		close(cmd[0]);
		close(f1);
		close(cmd[1]);
		exit(EXIT_FAILURE);
	}
	close(cmd[0]);
	close(f1);
	close(cmd[1]);
	execute_process(argv[2], envp);
	exit(EXIT_SUCCESS);
}

void	pipex(int f1, int f2, char **ag, char **envp)
{
	int		end[2];
	pid_t	parent1;
	pid_t	parent2;

	if (pipe(end) == -1)
		error();
	parent1 = fork();
	if (parent1 == -1)
		error();
	if (parent1 == 0)
		child_process(f1, end, ag, envp);
	parent2 = fork();
	if (parent2 == -1)
		error();
	if (parent2 == 0)
		parent_process(f2, end, ag, envp);
	close(end[0]);
	close(end[1]);
	waitpid(parent1, NULL, 0);
	waitpid(parent2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	if (argc == 5)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
		{
			perror("open: ");
			exit(EXIT_FAILURE);
		}
		outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
		{
			perror("open: ");
			exit(EXIT_FAILURE);
		}
		pipex(infile, outfile, argv, envp);
	}
	else
	{
		fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}
