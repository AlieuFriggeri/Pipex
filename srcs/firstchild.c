/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstchild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:49:54 by afrigger          #+#    #+#             */
/*   Updated: 2022/11/29 16:05:47 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	firstchild(t_pipe *pipex, char **envp, char**args, int fd[2])
{
	int stdinput;

	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	stdinput = open(args[1], O_RDONLY);
	dup2(stdinput, 0);
	close(stdinput);
	splitpath(envp, pipex);
	set_args(pipex, args[2]);
	testpath(pipex);
	if (execve(pipex->pathok, pipex->cmd1_args, envp) == -1)
		printf("ERROR IN FIRST CHILD EXEC OCCURED");
}

/* int	readpipe(char *buffer)
{
	while (get_next_line(bite))
} */

void	secondchild(t_pipe *pipex, char **envp, char**args, int fd[2])
{
	char data[1000001];
	int output;

	//read(fd[0], data, 1000000);
	//printf("data is %s ok\n", data);
	output = open(args[4], O_WRONLY | O_CREAT, 0777);
	dup2(output, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(output);
	splitpath(envp, pipex);
	set_args(pipex, args[3]);
	testpath(pipex);
	if (execve(pipex->pathok, pipex->cmd1_args, envp) == -1)
		printf("ERROR IN SECOND CHILD EXEC OCCURED");
}