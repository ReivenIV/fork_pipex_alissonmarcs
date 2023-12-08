/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:50:17 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/08 16:05:00 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handler(int status)
{
	if (status == 1)
		ft_putendl_fd("pipex: infile doesn't exits", 2);
	else if (status == 2)
		ft_putendl_fd("pipex: error in open/creating outfile", 2);
	exit(1);
}
