/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:39:17 by antauber          #+#    #+#             */
/*   Updated: 2024/12/11 17:43:40 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	
	parsing(argc, argv, env);
	init_data(&data);
	open_files(argv, &data);
	// * CREATE PIPES
	
	// * CREATE FORKS

	// * WAIT CHILD
	
	// * HANDLE CMDS

	// * CLEAN

	clean_data(&data, 0);
	return (0);
}