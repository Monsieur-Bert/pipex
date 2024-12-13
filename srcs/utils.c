/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:06:49 by antauber          #+#    #+#             */
/*   Updated: 2024/12/13 18:03:17 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	init_data(t_data *data, int argc, char **argv)
{
	data->paths = NULL;
	data->n_paths = 0;
	data->only_cmd = NULL;
	data->n_cmdp = (argc - 3);
	data->cmdp = ft_calloc((data->n_cmdp + 1), sizeof(char *));
	data->child.fd_infile = open(argv[1], O_RDONLY);
	if (data->child.fd_infile == -1)
		clean_data(data, 1, ERR_INFILE);
	data->child.fd_outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->child.fd_outfile == -1)
		clean_data(data, 1, ERR_OUTFILE);
}


void	clean_child(t_child *child)
{
	if (child->fd_infile != -1)
	{
		close(child->fd_infile);
		child->fd_infile = -1;
	}
	if (child->fd_outfile != -1)
	{
		close(child->fd_outfile);
		child->fd_outfile = -1;
	}
}


void	clean_data(t_data *data, int flag, char *error)
{
	clean_child(&data->child);
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
