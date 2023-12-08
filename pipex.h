/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:03:28 by ekordi            #+#    #+#             */
/*   Updated: 2023/10/28 11:54:20 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "My_C_Library/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	argc_check(int argc);
int		ft_open(char **argv);
void	execute(char **argv, char **envp, int *p_fd);
char	*cmd_path(char *cmd, char **envp);
void	free_arrayofstrings(char **a);
char	**get_path(char **envp);

#endif
