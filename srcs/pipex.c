/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:00:35 by afrigger          #+#    #+#             */
/*   Updated: 2022/11/30 15:15:15 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	splitpath(char **envp, t_pipe *pipex)
{
	int	i;

	i = 0;
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	pipex->paths = ft_split(*envp + 5, ':');
}

void	testpath(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (pipex->paths[i] != NULL)
	{
		pipex->pathok = ft_strjoin(pipex->paths[i], "/");
		pipex->pathok = ft_strjoin(pipex->pathok, pipex->cmd1);
		if (access(pipex->pathok, F_OK | X_OK) == 0)
			break ;
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

void	errcheck(t_pipe *pipex)
{
	if (WIFEXITED(pipex->wstatus))
		pipex->statuscode = WEXITSTATUS(pipex->wstatus);
	if (pipex->statuscode != 0)
	{
		ft_printf("exited with status code %d\n", pipex->statuscode);
		perror(strerror(pipex->statuscode));
		exit(0);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_pipe	pipex;
	t_pipe	pipex2;
	int		fd[2];

	if (ac != 5)
	{
		errno = 22;
		perror(strerror(errno));
		return (errno);
	}
	pipe(fd);
	pipex.id = fork();
	if (pipex.id == 0)
		firstchild(&pipex, envp, av, fd);
	waitpid(pipex.id, &pipex.wstatus, 0);
	close(fd[1]);
	pipex2.id = fork();
	if (pipex2.id == 0)
		secondchild(&pipex2, envp, av, fd);
	waitpid(pipex2.id, &pipex2.wstatus, 0);
	//these prints cause problems with the tester (remove them after test)
	ft_printf("exited with status code %d\n", errno);
	ft_printf("exited 2 with status code %d\n", pipex2.wstatus);
	return (0);
}
