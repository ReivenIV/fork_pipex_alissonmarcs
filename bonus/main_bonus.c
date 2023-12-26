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

static void	run_first_command(t_pipex *pipex);
static void	run_last_command(t_pipex *pipex);
static void	run_middle_commands(t_pipex *pipex, int command_index);
static void	create_childs(t_pipex *pipex, int command_index);

int	main(int argc, char *argv[], char *env[])
{
	t_pipex		pipex;
	int			command_index;

	command_index = init_pipex(&pipex, argc, argv, env);
	while (command_index <= argc - 2)
		create_childs(&pipex, command_index++);
	ft_free_split(pipex.path);
	exit(get_exit_status(pipex.exit_status_last_command));
}

static void	create_childs(t_pipex *pipex, int command_index)
{
	if (command_index == 2 || (command_index == 3 && pipex->here_doc))
		run_first_command(pipex);
	else if (command_index == pipex->parent_argc - 2)
		run_last_command(pipex);
	else
		run_middle_commands(pipex, command_index);
}

static void	run_first_command(t_pipex *pipex)
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
		infile = open_infile(pipex);
		dup2(infile, STDIN_FILENO);
		dup2(tube[1], STDOUT_FILENO);
		close(infile);
		close(tube[1]);
		execute(pipex, pipex->parent_argv[2 + pipex->here_doc]);
	}
	dup2(tube[0], STDIN_FILENO);
	close(tube[0]);
	close(tube[1]);
}

static void	run_last_command(t_pipex *pipex)
{
	char	*last_command;
	int		exit_status;
	int		outfile;
	pid_t	pid;

	last_command = pipex->parent_argv[pipex->parent_argc - 2];
	pid = fork();
	if (pid == 0)
	{
		outfile = open_outfile(pipex);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		execute(pipex, last_command);
	}
	waitpid(pid, &exit_status, 0);
	pipex->exit_status_last_command = exit_status;
}

static void	run_middle_commands(t_pipex *pipex, int command_index)
{
	char	*command;
	int		tube[2];
	pid_t	pid;

	command = pipex->parent_argv[command_index];
	if (pipe(tube) == -1)
		error_handler(pipex, 1, NULL);
	pid = fork();
	if (pid == 0)
	{
		close(tube[0]);
		dup2(tube[1], STDOUT_FILENO);
		close(tube[1]);
		execute(pipex, command);
	}
	else
	{
		close(tube[1]);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
	}
}
