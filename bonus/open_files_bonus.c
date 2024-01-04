/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 21:07:36 by alisson           #+#    #+#             */
/*   Updated: 2024/01/04 12:02:54 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_infile(t_pipex *pipex)
{
	int		infile;

	infile = open(pipex->parent_argv[1], O_RDONLY);
	if (infile == -1)
		error_handler(pipex, 1, pipex->parent_argv[1]);
	return (infile);
}

int	open_outfile(t_pipex *pipex)
{
	int		outfile;
	char	*file_name;

	file_name = pipex->parent_argv[pipex->parent_argc - 1];
	if (pipex->here_doc)
		outfile = open(file_name, O_RDWR | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		outfile = open(file_name, O_RDWR | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (outfile == -1)
		error_handler(pipex, 1, file_name);
	return (outfile);
}

int	here_doc(t_pipex *pipex, char *delimiter)
{
	int		tube[2];
	char	*line;

	if (pipe(tube) == -1)
		error_handler(pipex, 1, NULL);
	while (TRUE)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(0);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			get_next_line(-1);
			free(line);
			break ;
		}
		ft_putstr_fd(line, tube[1]);
		free(line);
	}
	close(tube[1]);
	return (tube[0]);
}

void	error_handler(t_pipex *pipex, int exit_status, char *msg)
{
	if (exit_status == 1)
	{
		ft_free_split(pipex->path);
		ft_putstr_fd("pipex: ", 2);
		perror(msg);
	}
	else if (exit_status == 2)
		ft_putstr_fd("pipex: split function failed\n", 2);
	else if (exit_status == 3)
		ft_putstr_fd("Invalid arguments. Take a look in "
			"https://github.com/alissonmarcs/pipex for examples of usage.\n",
			2);
	else if (exit_status == 127)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(msg);
		ft_free_split(pipex->path);
	}
	exit(exit_status);
}
