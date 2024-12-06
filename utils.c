/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stalash <stalash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:36:46 by stalash           #+#    #+#             */
/*   Updated: 2024/05/29 20:24:30 by stalash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_process(char *cmd, char **envp)
{
	char	**path_from_envp;
	char	**mypaths;
	char	*next_path;
	char	*path;
	int		i;

	path_from_envp = envp;
	while (*path_from_envp && ft_strncmp(*path_from_envp, "PATH=", 5) != 0)
		path_from_envp++;
	mypaths = ft_split(*path_from_envp + 5, ':');
	i = -1;
	while (mypaths[++i])
	{
		next_path = ft_strjoin(mypaths[i], "/");
		path = ft_strjoin(next_path, cmd);
		free(next_path);
		if (access(path, F_OK) == 0)
		{
			free_split(mypaths);
			return (path);
		}
		free(path);
	}
	free_split(mypaths);
	return (NULL);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}
