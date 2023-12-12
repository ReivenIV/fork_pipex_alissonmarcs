/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisson <alisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:50:17 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/12 13:50:00 by alisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handler(int status, char *msg)
{
	if (status == 1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(msg);
	}
	else if (status == 2)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(msg);
	}
	else if (status == 3)
		ft_putendl_fd("pipex: unable to create pipe", 2);
	else if (status == 4)
		ft_putendl_fd("pipex: failed to get path", 2);
	else if (status == 5)
		ft_putendl_fd("pipex: failed to split command string", 2);
	else if (status == 127)
		ft_putendl_fd("pipex: command not found", 2);
	exit(status);
}
