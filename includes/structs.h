/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:04:56 by antauber          #+#    #+#             */
/*   Updated: 2024/12/13 17:49:39 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_child
{
	int		fd_infile;
	int		fd_outfile;
}	t_child;

typedef struct s_data
{
	char	**paths;
	int		n_paths;
	char	*only_cmd;
	char	**cmdp;
	int		n_cmdp;
	t_child	child;
}	t_data;

#endif