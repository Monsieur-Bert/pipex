/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:39:17 by antauber          #+#    #+#             */
/*   Updated: 2024/12/23 10:20:33 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	check_arg(int argc)
{
	if (argc < 5)
	{
		ft_printf(2, "Error : Wrong number of arguments\n");
		exit (EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;

	i = 2;
	check_arg(argc);
	init_data(&data, argc, argv);
	parsing(&data, argc, argv, env);
	if (data.fd_in != -1)
	{
		if (dup2(data.fd_in, STDIN_FILENO))
			clean_data(&data, 1, ERR_DUP2, NULL);
	}
	else
		i++;
	while (i < argc - 1 - (data.fd_out == -1))
	{
		processes(&data, argv[i], env, (i - 2));
		i++;
	}
	while (wait(NULL) > 0)
		;
	clean_data(&data, 0, NULL, NULL);
	return (0);
}
