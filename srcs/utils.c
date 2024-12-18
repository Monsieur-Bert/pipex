/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:06:49 by antauber          #+#    #+#             */
/*   Updated: 2024/12/18 15:54:46 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	check_arg(int argc, char **argv)
{
	if (argc < 5) // ! change it for pipeline_manda > if (argc != 5)
	{
		ft_printf(2, "Error : Wrong number of arguments\n");
		exit (EXIT_FAILURE);
	}
	if (access(argv[1], F_OK) == -1)
		ft_error(1, ERR_INFILE, argv[1]);
	if (access(argv[argc - 1], F_OK) == 0)
	{
		if (access(argv[argc - 1], W_OK) == -1)
			ft_error(1, ERR_OUTFILE, argv[argc -1]);
	}
}

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
		clean_data(data, 1, ERR_INFILE, argv[1]);
	data->fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fd_out == -1)
		clean_data(data, 1, ERR_OUTFILE, argv[argc -1]);
}

void	close_files(t_data *data)
{
	close (data->fd_in);
	close (data->fd_out);
}

void	clean_data(t_data *data, int flag, char *error, char *name)
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
	close_files(data);
	if (flag != 0)
		ft_error(flag, error, name);
	exit (EXIT_SUCCESS);
}

void	ft_error(int flag, char *error, char *name)
{
	if (flag == 2)
		ft_printf(2, "Error : %s\n", ERR_MALL);
	else
		ft_printf(2, "Error%s\"%s\": %s\n", error, name, strerror(errno));
	exit (EXIT_FAILURE);
}
