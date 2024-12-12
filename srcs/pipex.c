/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:39:17 by antauber          #+#    #+#             */
/*   Updated: 2024/12/12 11:59:26 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	child_process(char *argv, char **env, t_data *data)
{
	char	**params;
	char	*pathname;
	int i;

	params = ft_split(argv, ' '); // ! security
	if (access(argv, X_OK) == -1)
	{
		if (data->paths == NULL)
			get_paths(env, data);
		i = 0;
		while (i < data->n_paths)
		{
			pathname = get_pathname(argv, data->paths[i]); // ! security
			if (access(pathname, X_OK) == 0)
			{
				free(pathname);
				break ;
			}
			free(pathname);
			i++;
		}
	}
	else
		pathname = ft_strdup(argv); // ! security
	if (execve(pathname, params, env) == -1)
	{
		free(pathname);
		//ft_free_tabstr(params); // todo find a way to calculate the size
		clean_data(data, 1, ERR_CMD);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	pid_t	pid;
	int		i;
	
	i = 2;
	init_data(&data);
	parsing(argc, argv, env, &data);
	open_files(argv, &data);
	// * CREATE PIPES
	
	// * WAIT CHILD
	
	// * HANDLE CMDS
	while (i < argc - 1)
	{
		pid = fork();
		if (pid == -1)
			clean_data(&data, 1, ERR_FORK);
		else if (pid == 0)
			child_process(argv[i], env, &data);
		else
		{
			wait(NULL);
			ft_printf(1, "Parent\n");
		}
		
		i++;
	}
	// * CLEAN
	clean_data(&data, 0, NULL);
	return (0);
}
