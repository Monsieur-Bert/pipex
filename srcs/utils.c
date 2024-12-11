/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:06:49 by antauber          #+#    #+#             */
/*   Updated: 2024/12/11 15:32:09 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

#include <stdio.h>
void	open_files(char **argv, t_data *data)
{
	data->fd_infile = open(argv[1], O_RDONLY);
	if (data->fd_infile == -1)
		clean_data(data, 1);
	data->fd_outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fd_outfile == -1)
		clean_data(data, 1);
}

void	init_data(t_data *data)
{
	data->fd_infile = -1;
	data->fd_outfile = -1;
}

void	clean_data(t_data *data, int error)
{
	if (data->fd_infile != -1)
		close (data->fd_infile);
	if (data->fd_outfile != -1)
		close (data->fd_outfile);
	if (error == 1)
		ft_error();
	exit (EXIT_SUCCESS);
}

void	ft_error(void)
{
	ft_printf(2, "Error : %s\n", strerror(errno));
	exit (EXIT_FAILURE);
}
