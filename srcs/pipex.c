/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:00:35 by afrigger          #+#    #+#             */
/*   Updated: 2022/11/28 15:07:05 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **splitpath(char **envp)
{
	int i;
	char **paths;

	i = 0;
	while(ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	paths = ft_split(*envp + 5, ':');
	return (paths);
}

char	*testpath(char **paths, char *cmd)
{
	int i;
	char *tmp;

	i = 0;
	while(paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK | X_OK) == 0)
			break;
		else
			free(tmp);
		i++;
	}
	return tmp;
}

void	set_args(t_pipe *pipex, char *args)
{
	char **tmp;
	int i;
	tmp = ft_split(args, ' ');
	pipex->cmd1 = tmp[0];
	//printf("%s\n", tmp[1]);

	i = 1;
	while (tmp[i] != NULL)
	{
		if(pipex->cmd1_args == NULL)
			pipex->cmd1_args = ft_strjoin("", tmp[i]);
		else
		{
			pipex->cmd1_args = ft_strjoin(pipex->cmd1_args, tmp[i]);
			pipex->cmd1_args = ft_strjoin(pipex->cmd1_args, " ");
		}
		i++;
	}
	//printf("%s\n", tmp[1]);
}

int main (int ac, char* av[], char *envp[])
{
	t_pipe pipex;
	int	id;
	int fd[2];

	pipex.paths = splitpath(envp);
	set_args(&pipex, av[2]);
	//pipex.cmd1 = av[1];
	printf("args for are %s\n", pipex.cmd1_args);
	pipex.pathok = testpath(pipex.paths, pipex.cmd1);
	printf("args for are %s\n", pipex.cmd1_args);
	printf("ok path for %s is %s\n", pipex.cmd1, pipex.pathok);
	(void)ac;
	
	printf("args for %s are %s\n", pipex.cmd1, pipex.cmd1_args);
	return 0;
	char *array[] =
	{
	    pipex.pathok,
	    av[4],
	    pipex.cmd1_args,
	    NULL
	};
	id = fork();
	if(id == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve(pipex.pathok, array, NULL);
	}
	else 
	{
		wait(NULL);
		// close(fd[1]);
		// int nbyte = read(fd[0], grepres, 1000);
		// close(fd[0]);
		// int file = open(av[4], O_WRONLY | O_CREAT, 0777);
		// printf("GREP RESULT IS %s\n", grepres);
		// write(file, &grepres, nbyte);
		// printf("lol jsuis apres le grep\n");
		// execve("//usr/bin/cat", array2, NULL);
	}
	  printf("lol jsuis apres le cat et le grep mdr\n");
	return 0;
}