/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:57:44 by antauber          #+#    #+#             */
/*   Updated: 2024/12/13 16:21:13 by antauber         ###   ########.fr       */
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

/*===== SRC/UTILS.C ==========================================================*/
void	open_files(char **argv, t_data *data);
void	init_data(t_data *data, int argc, char **argv);
void	clean_data(t_data *data, int flag, char *error);
void	ft_error(int flag, char *error);

/*===== SRC/PARSING.C ========================================================*/
char	*rm_option_n_spaces(char *cmd);
int		valid_path(t_data *data, int n_cmd);
void	get_paths(char **env, t_data *data);
char	*get_pathname(char *cmd, char *path);
void	check_arg(int argc);
void	parsing(int argc, char **argv, char **env, t_data *data);

#endif
