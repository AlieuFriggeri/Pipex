/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:50:18 by afrigger          #+#    #+#             */
/*   Updated: 2022/11/29 12:53:58 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../libft/libft.h"

typedef	struct s_pipe
{
	int		id;
	char	*cmd1;
	char	**cmd1_args;
	char	*file;
	char	**paths;
	char	*pathok;
}	t_pipe;

void	testpath(t_pipe *pipex);
void	splitpath(char **envp, t_pipe *pipex);

#endif