/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:50:18 by afrigger          #+#    #+#             */
/*   Updated: 2022/11/28 14:02:11 by afrigger         ###   ########.fr       */
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
	char	*cmd1;
	char	*cmd1_args;
	char	*cmd2;
	char	*cmd2_args;
	char	*filein;
	char	*fileout;
	char	**paths;
	char	*pathok;
}	t_pipe;

char	*testpath(char **paths, char *cmd);
char	**splitpath(char **envp);

#endif