/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:37:24 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/08 16:05:03 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex *pipex, int argc, char *argv[])
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		error_handler(1);
	pipex->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0700);
	if (pipex->outfile == -1)
		error_handler(2);
}
