/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:55:07 by almarcos          #+#    #+#             */
/*   Updated: 2024/01/03 16:52:21 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

enum e_bool
{
	FALSE,
	TRUE
};

typedef struct s_pipex
{
	int		here_doc;
	int		exit_status_last_command;
	int		parent_argc;
	char	**parent_argv;
	char	**parent_env;
	char	**path;
}			t_pipex;

/* helpers_bonus.c */
int			init_pipex(t_pipex *pipex, int argc, char **argv, char **env);
void		get_path(t_pipex *pipex);
void		execute(t_pipex *pipex, char *command);
char		*find_executable(t_pipex *pipex, char *name);
int			get_exit_status(int exit_status);

/* open_files_bonus.c */
int			open_infile(t_pipex *pipex);
int			open_outfile(t_pipex *pipex);
int			here_doc(t_pipex *pipex, char *delimiter);
void		error_handler(t_pipex *pipex, int exit_status, char *msg);

#endif
