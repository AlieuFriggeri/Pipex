/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstchild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:49:54 by afrigger          #+#    #+#             */
/*   Updated: 2023/02/28 12:12:51 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	filecheck(char *arg)
{
	if (access(arg, F_OK) == -1)
	{
		errno = ENOENT;
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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
	if (pipex->pathok == NULL)
		cmdnotfound(pipex);
	error = execve(pipex->pathok, pipex->cmd1_args, envp);
	if (error == -1)
		errcheck(pipex);
}

void	secondchild(t_pipe *pipex, char **envp, char**args, int fd[2])
{
	int	output;
	int	error;

	if (args[4])
	{
		unlink(args[4]);
		output = open(args[4], O_WRONLY | O_CREAT, 0777);
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	splitpath(envp, pipex);
	set_args(pipex, args[3]);
	testpath(pipex);
	if (pipex->pathok == NULL)
		cmdnotfound(pipex);
	error = execve(pipex->pathok, pipex->cmd1_args, envp);
	if (error == -1)
		errcheck(pipex);
}

void	cmdnotfound(t_pipe *pipex)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(pipex->cmd1, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
