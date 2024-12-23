/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:06:49 by antauber          #+#    #+#             */
/*   Updated: 2024/12/23 10:21:47 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	open_files(t_data *data, int argc, char **argv)
{
	if (access(argv[1], F_OK | R_OK) == -1)
	{
		data->fd_in = -1;
		ft_error(3, ERR_INFILE, argv[1]);
	}
	else
	{
		data->fd_in = open(argv[1], O_RDONLY);
		if (data->fd_in == -1)
			clean_data(data, 1, ERR_INFILE, argv[1]);
	}
	if (access(argv[argc - 1], F_OK) == 0)
	{
		if (access(argv[argc - 1], W_OK) == -1)
		{
			data->fd_out = -1;
			ft_error(3, ERR_OUTFILE, argv[argc -1]);
		}
	}
	if (access(argv[argc -1], W_OK) != -1 || access(argv[argc -1], F_OK) == -1)
	{
		data->fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (data->fd_out == -1)
			clean_data(data, 1, ERR_OUTFILE, argv[argc -1]);
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
	if (data->cmdp == NULL)
		clean_data(data, 2, ERR_MALL, NULL);
	open_files(data, argc, argv);
}

void	close_files(t_data *data)
{
	if (data->fd_in != -1)
	{
		close (data->fd_in);
		data->fd_in = -1;
	}
	if (data->fd_out != -1)
	{
		close (data->fd_out);
		data->fd_out = -1;
	}
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
	if (flag != 3)
		exit (EXIT_FAILURE);
}
