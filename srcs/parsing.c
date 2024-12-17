/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:14:54 by antauber          #+#    #+#             */
/*   Updated: 2024/12/17 15:33:21 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*rm_option_n_spaces(t_data *data, char *cmd)
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
	only_cmd = ft_substr(cmd, start, (end - start));
	if (only_cmd == NULL)
		clean_data(data, 2, ERR_MALL);
	return (only_cmd);
}

char	*get_pathname(char *cmd, char *path)
{
	char	*buffer;
	char	*pathname;

	buffer = ft_strjoin(path, "/");
	pathname = ft_strjoin(buffer, cmd); // ! code a multiple arg join + secu
	free(buffer);
	return (pathname);
}

int	valid_path(t_data *data, int n_cmd)
{
	int		i;
	char	*buffer;

	i = 0;
	while (i < data->n_paths)
	{
		buffer = get_pathname(data->only_cmd, data->paths[i]);
		if (buffer == NULL)
			clean_data(data, 2, ERR_MALL);
		if (access(buffer, X_OK) != -1)
		{
			data->cmdp[n_cmd] = ft_strdup(buffer);
			free(buffer);
			return (1);
		}
		free(buffer);
		i++;
	}
	return (0);
}

void	get_paths(t_data *data, char **env)
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
	data->paths = ft_split(envp, ':');
	if (data->paths == NULL)
		clean_data(data, 2, ERR_MALL);
	free(envp);
}

void	check_arg(int argc, char **argv)
{
	if (argc != 5) // ! change it for pipeline_bonus -> if (argc < 5)
	{
		ft_printf(2, "Error : Wrong number of arguments\n");
		exit (EXIT_FAILURE);
	}
	if (access(argv[1], F_OK) == -1)
		ft_error(1, ERR_INFILE);
}

void	parsing(t_data *data, int argc, char **argv, char **env)
{
	int		i_cmd;

	i_cmd = 2;
	check_arg(argc, argv);
	while (i_cmd < argc -1)
	{
		data->only_cmd = rm_option_n_spaces(data, argv[i_cmd]);
		if (access(data->only_cmd, X_OK) == -1)
		{
			if (data->paths == NULL)
				get_paths(data, env);
			if (!valid_path(data, i_cmd - 2))
				clean_data(data, 1, ERR_CMD);
		}
		else
		{
			data->cmdp[i_cmd - 2] = ft_strdup(data->only_cmd);
			if (data->cmdp[i_cmd - 2] == NULL)
				clean_data(data, 2, ERR_MALL);
		}
		i_cmd++;
		free(data->only_cmd);
		data->only_cmd = NULL;
	}
	data->cmdp[i_cmd - 2] = NULL;
}
