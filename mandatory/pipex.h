/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisson <alisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:55:07 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/13 11:44:59 by alisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include "../Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		tube[2];
	pid_t	first_child;
	pid_t	second_child;
	char 	**argv_childs;
	int		parent_argc;
	char	**parent_argv;
	char	**parent_env;
	char	**path;
}			t_pipex;

void		init_pipex(t_pipex *pipex, int argc, char **argv, char **env);
void		open_tube(t_pipex *pipex);
void 		close_tube(t_pipex *pipex);
void		first_child(t_pipex *pipex, char *command);
void		second_child(t_pipex *pipex, char *command);
void		get_path(t_pipex *pipex);
char		*find_executable(t_pipex *pipex);
void		execute(t_pipex *pipex, char *command);
void		free_split(char **split);
void		error_handler(t_pipex *pipex, int exit_status, char *msg);

#endif
