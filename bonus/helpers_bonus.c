/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:37:24 by almarcos          #+#    #+#             */
/*   Updated: 2024/01/03 17:00:11 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	init_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	if (argc < 5)
		error_handler(pipex, 3, NULL);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		pipex->here_doc = TRUE;
	else
		pipex->here_doc = FALSE;
	if (pipex->here_doc && argc < 6)
		error_handler(pipex, 3, NULL);
	pipex->parent_argc = argc;
	pipex->parent_argv = argv;
	pipex->parent_env = env;
	get_path(pipex);
	if (pipex->here_doc)
		return (3);
	return (2);
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

void	execute(t_pipex *pipex, char *command)
{
	char	*command_file;
	char	*command_not_found;
	char	**command_argv;

	if (command[0] == '\0')
		error_handler(pipex, 127, NULL);
	command_argv = ft_split(command, ' ');
	if (command_argv == NULL)
		error_handler(pipex, 2, NULL);
	command_file = find_executable(pipex, command_argv[0]);
	if (command_file == NULL)
	{
		command_not_found = ft_strdup(command_argv[0]);
		ft_free_split(command_argv);
		error_handler(pipex, 127, command_not_found);
	}
	execve(command_file, command_argv, pipex->parent_env);
}

char	*find_executable(t_pipex *pipex, char *name)
{
	char	*executable;
	char	*tmp;
	int		i;

	if (access(name, X_OK) == 0)
		return (name);
	i = 0;
	while (pipex->path[i])
	{
		tmp = ft_strjoin(pipex->path[i], "/");
		executable = ft_strjoin(tmp, name);
		free(tmp);
		if (access(executable, X_OK) == 0)
			return (executable);
		free(executable);
		i++;
	}
	return (NULL);
}

int	get_exit_status(int exit_status)
{
	return (((exit_status & 0xff00)) >> 8);
}
