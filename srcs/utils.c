/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:06:49 by antauber          #+#    #+#             */
/*   Updated: 2024/12/12 10:06:08 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	open_files(char **argv, t_data *data)
{
	data->fd_infile = open(argv[1], O_RDONLY);
	if (data->fd_infile == -1)
		clean_data(data, 1, ERR_INFILE);
	data->fd_outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fd_outfile == -1)
		clean_data(data, 1, ERR_OUTFILE);
}

void	init_data(t_data *data)
{
	data->fd_infile = -1;
	data->fd_outfile = -1;
	data->paths = NULL;
	data->n_paths = 0;
}

void	clean_data(t_data *data, int flag, char *error)
{
	if (data->fd_infile != -1)
		close (data->fd_infile);
	if (data->fd_outfile != -1)
		close (data->fd_outfile);
	if (data->paths != NULL)
	{
		ft_free_tabstr(data->paths,data->n_paths);
		data->paths = NULL;
	}
	if (flag == 1)
		ft_error(error);
	exit (EXIT_SUCCESS);
}

void	ft_error(char *error)
{
	ft_printf(2, "Error%s: %s\n", error, strerror(errno));
	exit (EXIT_FAILURE);
}
