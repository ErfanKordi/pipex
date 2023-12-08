/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:31:55 by ekordi            #+#    #+#             */
/*   Updated: 2023/12/06 16:30:43 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	execute(char **argv, char **envp, int *p_fd)
{
	char	**cmd;
	char	*cmdpath;
	int		fd;

	cmd = ft_split(argv[3], ' ');
	if (access(cmd[0], X_OK) == 0)
		cmdpath = cmd[0];
	else
		cmdpath = cmd_path(cmd[0], envp);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(p_fd[1]);
	dup2(fd, 1);
	close(fd);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	execve(cmdpath, cmd, envp);
	free_arrayofstrings(cmd);
}

void	argc_check(int argc)
{
	if (argc != 5)
	{
		printf("Usage: <infile> <cmd1> <cmd2> <outfile>\n");
		exit(1);
	}
}

void	free_arrayofstrings(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

char	**get_path(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

int	ft_open(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			ft_putstr_fd("zsh: permission denied: ", 2);
		else if (errno == ENOENT)
			ft_putstr_fd("zsh: no such file or directory: ", 2);
		else
			ft_putstr_fd("zsh: error opening the file: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}
