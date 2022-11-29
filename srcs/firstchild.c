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
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	splitpath(envp, pipex);
	set_args(pipex, args[2]);
	testpath(pipex);
	if (execve(pipex->pathok, pipex->cmd1_args, envp) == -1)
		printf("ERROR IN FIRST CHILD EXEC OCCURED");
}

void	secondchild(t_pipe *pipex, char **envp, char**args, int fd[2])
{
	char data[1000001];
	int fd2;

	read(fd[0], data, 1000000);
	printf("data is %s ok\n", data);
	fd2 = open(args[4], O_WRONLY | O_CREAT, 0777);
	dup2(fd2, 1);
	close(fd[1]);
	close(fd[0]);
	splitpath(envp, pipex);
	set_args(pipex, args[3]);
	testpath(pipex);
	if (execve(pipex->pathok, pipex->cmd1_args, envp) == -1)
		printf("ERROR IN SECOND CHILD EXEC OCCURED");
}