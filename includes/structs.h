/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:04:56 by antauber          #+#    #+#             */
/*   Updated: 2024/12/17 14:18:54 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data
{
	char	**paths;
	int		n_paths;
	char	*only_cmd;
	char	**cmdp;
	int		n_cmdp;
	int		fd_in;
	int		fd_out;
}	t_data;

#endif