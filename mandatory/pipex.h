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

#ifndef PIPEX_H

# define PIPEX_H
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		tube[2];
	pid_t	first_child;
	pid_t	second_child;
	char	**parent_argv;
	char	**parent_env;
	char	**argv_childs;
	char	**path;
}			t_pipex;

/* helpers.c */
void		init_pipex(t_pipex *pipex, int argc, char **argv, char **env);
void		open_tube(t_pipex *pipex);
void		close_tube(t_pipex *pipex);
void		get_path(t_pipex *pipex);
void		free_split(char **split);

/* error_handler.c */
void		error_handler(t_pipex *pipex, int exit_status, char *msg);

/* childs.c */
void		first_child(t_pipex *pipex, char *command);
void		second_child(t_pipex *pipex, char *command);
void		execute(t_pipex *pipex, char *command);
char		*find_executable(t_pipex *pipex);
int			get_exit_status(int exit_status);

#endif
