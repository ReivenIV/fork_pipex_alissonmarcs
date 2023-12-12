/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisson <alisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:37:24 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/12 10:18:10 by alisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex *pipex, int argc, char *argv[])
{
	pipex->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0700);
	if (pipex->outfile == -1)
		error_handler(2);
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		error_handler(1);
}

void init_tube(t_pipex *pipex)
{
	if (pipe(pipex->tube) == -1)
		error_handler(3);
}

void first_child(t_pipex *pipex, char *command)
{
	pipex->first_child = fork();
	if (pipex->first_child == 0)
	{
		close(pipex->tube[0]);
		dup2(pipex->tube[1], STDOUT_FILENO);
		dup2(pipex->infile, STDIN_FILENO);
		execute(pipex, command);
	}
}

void second_child(t_pipex *pipex, char *command)
{
	pipex->second_child = fork();
	if (pipex->second_child == 0)
	{
		close(pipex->tube[1]);
		dup2(pipex->tube[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		execute(pipex, command);
	}
}

void execute(t_pipex *pipex, char *command)
{
	char *path_to_exec;
	char **argv;
	
	argv = ft_split(command, ' ');
	if (argv == NULL)
		error_handler(5);
	path_to_exec = find_executable(pipex, argv[0]);
	if (!path_to_exec)
	{
		free_split(argv);
		free_split(pipex->path_env);
		error_handler(6);
	}
	execve(path_to_exec, argv, pipex->env);
}

char *find_executable(t_pipex *pipex, char *command)
{
	char *to_check;
	char *tmp;
	int i;

	if (ft_strncmp(command, "./", 2) == 0 && access(command, X_OK) == 0)
		return (command);
	i = 0;
	while (pipex->path_env[i])
	{
		tmp = ft_strjoin(pipex->path_env[i], "/");
		to_check = ft_strjoin(tmp, command);
		free(tmp);
		if (access(to_check, X_OK) == 0)
			return (to_check);
		free(to_check);
		i++;
	}
	return (NULL);
}

void get_path_env(t_pipex *pipex, char **env)
{
	char **path_env;
	int i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	env[i] += 5;
	path_env = ft_split(env[i], ':');
	if (path_env == NULL)
		error_handler(4);
	pipex->path_env = path_env;
}

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
