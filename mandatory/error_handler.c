/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisson <alisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:50:17 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/12 20:57:01 by alisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_handler(t_pipex *pipex, int exit_status, char *msg)
{
	if (exit_status == 1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(msg);
	}
	else if (exit_status == 2)
		ft_putstr_fd("pipex: split function failed\n", 2);
	else if (exit_status == 3)
		ft_putstr_fd("Invalid arguments. Take a look in " \
	"https://github.com/alissonmarcs/pipex for exemples of usage.\n", 2);
	else if (exit_status == 127)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(pipex->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_split(pipex->argv);
		free_split(pipex->path_env);
	}
	exit(exit_status);
}