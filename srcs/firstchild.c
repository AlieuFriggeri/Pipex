/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstchild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:49:54 by afrigger          #+#    #+#             */
/*   Updated: 2022/12/01 10:35:33 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	filecheck(char *arg)
{
	if (access(arg, F_OK) == -1)
	{
		errno = ENOENT;
		perror(strerror(errno));
		exit(errno);
	}
}

void	firstchild(t_pipe *pipex, char **envp, char**args, int fd[2])
{
	int	stdinput;
	int	error;

	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	stdinput = open(args[1], O_RDONLY);
	dup2(stdinput, 0);
	close(stdinput);
	splitpath(envp, pipex);
	set_args(pipex, args[2]);
	testpath(pipex);
	filecheck(args[1]);
	error = execve(pipex->pathok, pipex->cmd1_args, envp);
	exit(-1);
}

void	secondchild(t_pipe *pipex, char **envp, char**args, int fd[2])
{
	int	output;
	int	error;

	unlink(args[4]);
	output = open(args[4], O_WRONLY | O_CREAT, 0777);
	dup2(output, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(output);
	splitpath(envp, pipex);
	set_args(pipex, args[3]);
	testpath(pipex);
	error = execve(pipex->pathok, pipex->cmd1_args, envp);
	if (error == -1)
		errcheck(pipex);
}
