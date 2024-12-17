/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:06:49 by antauber          #+#    #+#             */
/*   Updated: 2024/12/17 11:46:20 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	init_data(t_data *data, int argc, char **argv)
{
	(void)argv;
	data->paths = NULL;
	data->n_paths = 0;
	data->only_cmd = NULL;
	data->n_cmdp = (argc - 3);
	data->cmdp = ft_calloc((data->n_cmdp + 1), sizeof(char *));
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in == -1)
		clean_data(data, 1, ERR_INFILE);
	data->fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fd_out == -1)
		clean_data(data, 1, ERR_OUTFILE);
}

void	clean_data(t_data *data, int flag, char *error)
{
	if (data->paths != NULL)
	{
		ft_free_tabstr(data->paths, data->n_paths);
		data->paths = NULL;
	}
	if (data->only_cmd != NULL)
	{
		free(data->only_cmd);
		data->only_cmd = NULL;
	}
	if (data->cmdp != NULL)
	{
		ft_free_tabstr(data->cmdp, data->n_cmdp);
		data->cmdp = NULL;
	}
	close (data->fd_in);
	close (data->fd_out);
	if (flag != 0)
		ft_error(flag, error);
	exit (EXIT_SUCCESS);
}

void	ft_error(int flag, char *error)
{
	if (flag == 1)
		ft_printf(2, "Error%s: %s\n", error, strerror(errno));
	if (flag == 2)
		ft_printf(2, "Error : %s\n", ERR_MALL);
	exit (EXIT_FAILURE);
}
