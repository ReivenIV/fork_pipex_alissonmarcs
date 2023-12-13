/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisson <alisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:55:07 by almarcos          #+#    #+#             */
/*   Updated: 2023/12/13 11:04:58 by alisson          ###   ########.fr       */
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
	char	**path_env;
	char	**env;
	char 	**argv;
	char	**parent_argv;
	int		parent_argc;
}			t_pipex;

void		error_handler(t_pipex *pipex, int exit_status, char *msg);
void		init_tube(t_pipex *pipex);
void		get_path_env(t_pipex *pipex);
void		execute(t_pipex *pipex, char *command);
void		first_child(t_pipex *pipex, char *command);
char		*find_executable(t_pipex *pipex);
void		free_split(char **split);
void		second_child(t_pipex *pipex, char *command);
void 		close_files(t_pipex *pipex);
void		init_pipex(t_pipex *pipex, int argc, char **argv, char **env);

#endif
