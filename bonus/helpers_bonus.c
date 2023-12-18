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
	pipex->parent_argc = argc;
	pipex->parent_argv = argv;
	pipex->parent_env = env;
	get_path(pipex);
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

void	execute(t_pipex *pipex, char *command)
{
	char	*executable;
	char	**argv;

	argv = ft_split(command, ' ');
	if (argv == NULL)
		error_handler(pipex, 2, NULL);
	executable = find_executable(pipex, argv[0]);
	if (executable == NULL)
	{
		free_split(argv);
		error_handler(pipex, 127, NULL);
	}
	execve(executable, argv, pipex->parent_env);
}

char	*find_executable(t_pipex *pipex, char *name)
{
	char	*executable;
	char	*tmp;
	int		i;

	if ((ft_strncmp(name, "./", 2) == 0 || name[0] == '/')
		&& access(name, X_OK) == 0)
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

// void create_childs(t_pipex *pipex, int command_index)
// {
// 	if (command_index == 2)
// 		run_first_command(pipex);
// 	else if (command_index == pipex->parent_argc - 2)
// 		run_last_command(pipex);
// 	else
// 		run_middle_commands(pipex, command_index);
// }

void run_first_command(t_pipex *pipex)
{
	int		infile;
	int		tube[2];
	pid_t	pid;

	if (pipe(tube) == -1)
		error_handler(pipex, 1, NULL);
	pid = fork();
	if (pid == 0)
	{
		close(tube[0]);
		infile = open(pipex->parent_argv[1], O_RDONLY);
		if (infile == -1)
		{
			close(tube[1]);
			error_handler(pipex, 1, pipex->parent_argv[1]);
		}
		dup2(infile, STDIN_FILENO);
		dup2(tube[1], STDOUT_FILENO);
		close(infile);
		close(tube[1]);
		execute(pipex, pipex->parent_argv[2]);
	}
	dup2(tube[0], STDIN_FILENO);
	close(tube[1]);
	close(tube[0]);
	waitpid(pid, NULL, 0);
}

void run_last_command(t_pipex *pipex)
{
	char	*last_command;
	char	*outfile_name;
	int		outfile_fd;
	int		exit_status;
	pid_t	pid;

	last_command = pipex->parent_argv[pipex->parent_argc - 2];
	outfile_name = pipex->parent_argv[pipex->parent_argc - 1];
	pid = fork();
	if (pid == 0)
	{
		outfile_fd = open(outfile_name, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (outfile_fd == -1)
			error_handler(pipex, 1, outfile_name);
		dup2(outfile_fd, STDOUT_FILENO);
		execute(pipex, last_command);
	}
	waitpid(pid, &exit_status, 0);
	pipex->exit_status_last_command = exit_status;
}