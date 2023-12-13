/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisson <alisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:37:24 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/13 11:04:52 by alisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void init_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->parent_argv = argv;
	pipex->parent_argc = argc;
	pipex->env = env;
	get_path_env(pipex);
	init_tube(pipex);
}

void close_files(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

void init_tube(t_pipex *pipex)
{
	if (pipe(pipex->tube) == -1)
		error_handler(pipex, 1, NULL);
}

void first_child(t_pipex *pipex, char *command)
{
	int infile;

	pipex->first_child = fork();
	if (pipex->first_child == 0)
	{
		close(pipex->tube[0]);
		infile = open(pipex->parent_argv[1], O_RDONLY);
		if (infile == -1)
		{
			close(pipex->tube[1]);
			free_split(pipex->path_env);
			error_handler(pipex, 1, pipex->parent_argv[1]);
		}
		dup2(pipex->tube[1], STDOUT_FILENO);
		dup2(infile, STDIN_FILENO);
		execute(pipex, command);
	}
}

void second_child(t_pipex *pipex, char *command)
{
	int outfile;

	pipex->second_child = fork();
	if (pipex->second_child == 0)
	{
		close(pipex->tube[1]);
		outfile = open(pipex->parent_argv[pipex->parent_argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0700);
		if (outfile == -1)
		{
			close(pipex->tube[0]);
			free_split(pipex->path_env);
			error_handler(pipex, 1, pipex->parent_argv[pipex->parent_argc - 1]);
		}
		dup2(pipex->tube[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		execute(pipex, command);
	}
}

void execute(t_pipex *pipex, char *command)
{
	char *executable;
	
	pipex->argv = ft_split(command, ' ');
	if (pipex->argv == NULL)
		error_handler(pipex, 2, NULL);
	executable = find_executable(pipex);
	if (executable == NULL)
		error_handler(pipex, 127, NULL);
	execve(executable, pipex->argv, pipex->env);
}

char *find_executable(t_pipex *pipex)
{
	char *executable;
	char *command;
	char *tmp;
	int i;

	command = pipex->argv[0];
	if (ft_strncmp(command, "./", 2) == 0 && access(command, X_OK) == 0)
		return (command);
	i = 0;
	while (pipex->path_env[i])
	{
		tmp = ft_strjoin(pipex->path_env[i], "/");
		executable = ft_strjoin(tmp, command);
		free(tmp);
		if (access(executable, X_OK) == 0)
			return (executable);
		free(executable);
		i++;
	}
	return (NULL);
}

void get_path_env(t_pipex *pipex)
{
	char **path_env;
	char **env;

	env = pipex->env;
	while (ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	*env += 5;
	path_env = ft_split(*env, ':');
	if (path_env == NULL)
		error_handler(pipex, 2, NULL);
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
