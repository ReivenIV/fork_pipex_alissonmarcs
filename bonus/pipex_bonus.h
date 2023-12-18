/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisson <alisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:55:07 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/14 15:37:02 by alisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		exit_status_last_command;
	int		parent_argc;
	char	**parent_argv;
	char	**parent_env;
	char	**path;
}			t_pipex;

void		init_pipex(t_pipex *pipex, int argc, char **argv, char **env);
void		get_path(t_pipex *pipex);
void		free_split(char **split);
void		create_childs(t_pipex *pipex, int command_index);
void		execute(t_pipex *pipex, char *command);
char		*find_executable(t_pipex *pipex, char *name);
int			get_exit_status(int exit_status);
void		error_handler(t_pipex *pipex, int exit_status, char *msg);
void		run_first_command(t_pipex *pipex);
void		run_last_command(t_pipex *pipex);

#endif
