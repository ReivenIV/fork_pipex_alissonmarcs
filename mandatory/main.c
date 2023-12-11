/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:55:10 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/09 15:33:12 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int exit_status;

	open_files(&pipex, argc, argv);
	get_path_env(&pipex, env);
	pipex.env = env;
	init_tube(&pipex);
	//close(pipex.tube[1]);
	first_child(&pipex, argv[2]);
	waitpid(pipex.first_child, NULL, 0);
	second_child(&pipex, argv[3]);
	close(pipex.infile);
	close(pipex.outfile);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.second_child, &exit_status, 0);
	exit(WEXITSTATUS(exit_status));
}
