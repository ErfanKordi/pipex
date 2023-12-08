/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:34:00 by ekordi            #+#    #+#             */
/*   Updated: 2023/12/07 14:09:12 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*cmd_path(char *cmd, char **envp)
{
	char	*temp;
	char	**paths;
	int		i;
	char	*path;

	paths = get_path(envp);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		temp = ft_strjoin(path, cmd);
		if (access(temp, X_OK) == 0)
		{
			free_arrayofstrings(paths);
			free(path);
			return (temp);
		}
		free(temp);
		free(path);
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	free_arrayofstrings(paths);
	exit(127);
}

int	child(char **argv, int *p_fd, char **envp)
{
	char	**cmd;
	char	*cmdpath;
	int		fd;

	fd = ft_open(argv);
	if (fd == -1)
		return (1);
	cmd = ft_split(argv[2], ' ');
	if (access(cmd[0], X_OK) == 0)
		cmdpath = cmd[0];
	else
		cmdpath = cmd_path(cmd[0], envp);
	close(p_fd[0]);
	dup2(fd, 0);
	close(fd);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	execve(cmdpath, cmd, envp);
	free_arrayofstrings(cmd);
	return (0);
}

void	parent(char **argv, int *p_fd, char **envp)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		execute(argv, envp, p_fd);
	close(p_fd[1]);
	waitpid(pid, &status, 0);
	status = WEXITSTATUS(status);
	exit(status);
}

int	main(int argc, char **argv, char **envp)
{
	int	p_fd[2];
	int	pid1;

	argc_check(argc);
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0)
		child(argv, p_fd, envp);
	else
		parent(argv, p_fd, envp);
	waitpid(pid1, 0, 0);
	return (0);
}
