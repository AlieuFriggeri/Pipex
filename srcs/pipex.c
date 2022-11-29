/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:00:35 by afrigger          #+#    #+#             */
/*   Updated: 2022/11/29 13:47:40 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	splitpath(char **envp, t_pipe *pipex)
{
	int i;

	i = 0;
	while(ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	pipex->paths = ft_split(*envp + 5, ':');
}

void	testpath(t_pipe *pipex)
{
	int i;

	i = 0;
	while(pipex->paths[i] != NULL)
	{
		pipex->pathok = ft_strjoin(pipex->paths[i], "/");
		pipex->pathok = ft_strjoin(pipex->pathok, pipex->cmd1);
		if (access(pipex->pathok, F_OK | X_OK) == 0)
			break;
		else
		{
			free(pipex->pathok);
			pipex->pathok = NULL;
		}
		i++;
	}
}

void	set_args(t_pipe *pipex, char *args)
{

	pipex->cmd1_args = ft_split(args, ' ');
	pipex->cmd1 = pipex->cmd1_args[0];
}


int main (int ac, char* av[], char *envp[])
{
	t_pipe pipex;
	t_pipe pipex2;

	splitpath(envp, &pipex);
	set_args(&pipex, av[2]);
	testpath(&pipex);
	splitpath(envp, &pipex2);
	set_args(&pipex2, av[3]);
	testpath(&pipex2);
	//ft_vector(&pipex);
	(void)ac;
	// char *array[] =
	// {
	//     pipex.pathok,
	//     pipex.cmd1_args[1],
	// 	NULL
	// };
	ft_printf("execve cmd is %s\n", pipex.cmd1);
	ft_printf("execve path is %s\n", pipex.pathok);
	ft_printf("execve args are %s %s %s %s\n", pipex.cmd1_args[0], pipex.cmd1_args[1], pipex.cmd1_args[2], pipex.cmd1_args[3]);
	ft_printf("execve2 cmd is %s\n", pipex2.cmd1);
	ft_printf("execve2 path is %s\n", pipex2.pathok);
	ft_printf("execve2 args are %s %s %s %s\n", pipex2.cmd1_args[0], pipex2.cmd1_args[1], pipex2.cmd1_args[2], pipex2.cmd1_args[3]);
	printf("lol jsuis apres le cat et le grep mdr\n");
	pipex.id = fork();
	if (pipex.id == 0)
	{
		execve(pipex.pathok, pipex.cmd1_args, envp);
	}
	waitpid(pipex.id, NULL, 0);
	printf("ca a marcher");
	pipex2.id = fork();
	if(pipex2.id == 0)
	{
		execve(pipex2.pathok, pipex2.cmd1_args, envp);
	}
	waitpid(pipex2.id, NULL, 0);
	printf("ca a marcher 2");

	return 0;
}