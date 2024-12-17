/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:57:44 by antauber          #+#    #+#             */
/*   Updated: 2024/12/17 13:39:25 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

# include "../libft/includes/libft.h"
# include <structs.h>
# include <macros.h>

# include <stdio.h> // ! A supprimer c'est printf olala

/*===== SRCS/UTILS.C =========================================================*/
void	init_data(t_data *data, int argc, char **argv);
void	clean_data(t_data *data, int flag, char *error);
void	ft_error(int flag, char *error);

/*===== SRCS/PROCESSES.C =====================================================*/
void	exec_process(t_data *data, char *argv, char **env, int i_cmd);
void	child_process(t_data *data, char *argv, char **env, int i_cmd);

/*===== SRCS/PARSING.C =======================================================*/
char	*rm_option_n_spaces(t_data *data, char *cmd);
int		valid_path(t_data *data, int n_cmd);
void	get_paths(t_data *data, char **env);
char	*get_pathname(char *cmd, char *path);
void	check_arg(int argc, char **argv);
void	parsing(t_data *data, int argc, char **argv, char **env);

#endif
