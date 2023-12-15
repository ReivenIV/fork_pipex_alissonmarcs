/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisson <alisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:37:24 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/14 15:25:00 by alisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
