/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:37:24 by almarcos          #+#    #+#             */
/*   Updated: 2024/01/03 17:00:49 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	if (argc != 5)
		error_handler(pipex, 3, NULL);
	pipex->parent_argv = argv;
	pipex->parent_env = env;
	get_path(pipex);
	open_tube(pipex);
}

void	open_tube(t_pipex *pipex)
{
	if (pipe(pipex->tube) == -1)
		error_handler(pipex, 1, NULL);
}

void	close_tube(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

void	get_path(t_pipex *pipex)
{
	char	**path;
	char	**env;

	env = pipex->parent_env;
	while (ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	*env += 5;
	path = ft_split(*env, ':');
	if (path == NULL)
		error_handler(pipex, 2, NULL);
	pipex->path = path;
}

int	get_exit_status(int exit_status)
{
	return (((exit_status & 0xff00)) >> 8);
}
