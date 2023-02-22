/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:50:18 by afrigger          #+#    #+#             */
/*   Updated: 2023/02/22 11:38:11 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_pipe
{
	int		id;
	char	*cmd1;
	char	**cmd1_args;
	char	*file;
	char	**paths;
	char	*pathok;
	int		wstatus;
	int		statuscode;
}	t_pipe;

void	testpath(t_pipe *pipex);
void	splitpath(char **envp, t_pipe *pipex);
void	firstchild(t_pipe *pipex, char **envp, char**args, int fd[2]);
void	set_args(t_pipe *pipex, char *args);
void	secondchild(t_pipe *pipex, char **envp, char**args, int fd[2]);
void	errcheck(t_pipe *pipex);
void	cmdnotfound(t_pipe *pipex);
void	filecheck(char *arg);

#endif