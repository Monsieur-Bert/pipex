/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:39:17 by antauber          #+#    #+#             */
/*   Updated: 2024/12/17 15:11:42 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;

	i = 2;
	init_data(&data, argc, argv);
	parsing(&data, argc, argv, env);
	if (dup2(data.fd_in, STDIN_FILENO))
		clean_data(&data, 1, ERR_DUP2);
	while (wait(NULL) > 0)
		;
	while (i < argc - 2)
	{
		child_process(&data, argv[i], env, (i - 2));
		i++;
	}
	if (dup2(data.fd_out, STDOUT_FILENO) == -1)
		clean_data(&data, 1, ERR_DUP2);
	exec_process(&data, argv[i], env, (i - 2));
	clean_data(&data, 0, NULL);
	return (0);
}
