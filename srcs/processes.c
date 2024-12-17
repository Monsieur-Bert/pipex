/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:09:03 by antauber          #+#    #+#             */
/*   Updated: 2024/12/17 14:18:49 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	exec_process(t_data *data, char *argv, char **env, int i_cmd)
{
	char	**params;
	int		size;

	data->only_cmd = rm_option_n_spaces(data, data->cmdp[i_cmd]);
	if (data->only_cmd == NULL)
		clean_data(data, 2, ERR_MALL);
	params = ft_split(argv, ' ');
	if (params == NULL)
		clean_data(data, 2, ERR_MALL);
	size = ft_count_words(argv, ' ');
	if (execve(data->only_cmd, params, env) == -1)
	{
		ft_free_tabstr(params, size);
		params = NULL;
		clean_data(data, 1, ERR_CMD);
	}
}

void	child_process(t_data *data, char *argv, char **env, int i_cmd)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		clean_data(data, 1, ERR_PIPE);
	pid = fork();
	if (pid == -1)
		clean_data(data, 1, ERR_FORK);
	else if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2);
		close (pipefd[1]);
		exec_process(data, argv, env, i_cmd);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2);
		close (pipefd[0]);
	}
}
