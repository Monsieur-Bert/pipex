/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:14:54 by antauber          #+#    #+#             */
/*   Updated: 2024/12/12 11:54:27 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*rm_option_n_spaces(char *cmd)
{
	char	*only_cmd;
	int		start;
	int		end;

	start = 0;
	while (cmd[start] && cmd[start] == ' ')
		start++;
	end = start;
	while (cmd[end] && cmd[end] != ' ')
		end++;
	only_cmd = ft_substr(cmd, start, (end - start)); // ! security
	return (only_cmd);
}

char	*get_pathname(char *cmd, char *path)
{
	char	*buffer;
	char	*only_cmd;
	char	*pathname;

	only_cmd = rm_option_n_spaces(cmd);

	buffer = ft_strjoin(path, "/");
	pathname = ft_strjoin(buffer, only_cmd); // ! code a multiple arg Malloc
	free(only_cmd);
	free(buffer);
	return (pathname);
}

int	valid_path(char *cmd, t_data *data)
{
	int		i;
	char	*pathname;
	
	i = 0;
	while (i < data->n_paths)
	{
		pathname = get_pathname(cmd, data->paths[i]); // ! security
		if (access(pathname, X_OK) != -1)
		{
			free(pathname);
			return (1);
		}
		free(pathname);
		i++;
	}
	return (0);
}

void	get_paths(char **env, t_data *data)
{
	int		i;
	char	*envp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	envp = ft_strtrim(env[i], "PATH=");
	data->n_paths = ft_count_words(envp, ':');
	data->paths = ft_split(envp, ':'); // ! security
	free(envp);
}

void	parsing(int argc, char **argv, char **env, t_data *data)
{
	int	n_cmd;

	n_cmd  = 2;
	if (argc != 5) // ! change it for pipeline_bonus
	{
		ft_printf(2, "Error : Wrong number of arguments\n");
		exit (EXIT_FAILURE);
	}
	if (access(argv[1], F_OK) == -1)
		ft_error(ERR_INFILE);
	while (n_cmd < argc -1)
	{
		if (access(argv[n_cmd], X_OK) == -1)
		{
			if (data->paths == NULL)
				get_paths(env, data);
			if (!valid_path(argv[n_cmd], data))
				clean_data(data, 1, ERR_CMD);
		}
		n_cmd++;
	}
	// ? clean_data(data, 0, NULL);
}
