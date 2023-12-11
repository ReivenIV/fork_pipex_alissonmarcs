/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:50:17 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/09 12:58:43 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handler(int status)
{
	if (status == 1)
		ft_putendl_fd("pipex: infile doesn't exits", 2);
	else if (status == 2)
		ft_putendl_fd("pipex: error in open/creating outfile", 2);
	else if (status == 3)
		ft_putendl_fd("pipex: unable to create pipe", 2);
	else if (status == 4)
		ft_putendl_fd("pipex: failed to get path", 2);
	else if (status == 5)
		ft_putendl_fd("pipex: failed to split command string", 2);
	else if (status == 6)
		ft_putendl_fd("pipex: command doesn't exits", 2);
	exit(status);
}
