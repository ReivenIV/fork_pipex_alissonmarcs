/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisson <alisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:55:10 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/14 15:17:21 by alisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	init_pipex(&pipex, argc, argv, env);
	run_first_command(&pipex);
	run_last_command(&pipex);
	free_split(pipex.path);
	exit(get_exit_status(pipex.exit_status_last_command));
}