/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:57:44 by antauber          #+#    #+#             */
/*   Updated: 2024/12/12 11:49:35 by antauber         ###   ########.fr       */
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
void	init_data(t_data *data);
void	clean_data(t_data *data, int flag, char *error);
void	ft_error(char *error);

/*===== SRC/PARSING.C ========================================================*/
char	*rm_option_n_spaces(char *cmd);
int		valid_path(char *cmd, t_data *data);
void	get_paths(char **env, t_data *data);
char	*get_pathname(char *cmd, char *path);
void	parsing(int argc, char **argv, char **env, t_data *data);

#endif
