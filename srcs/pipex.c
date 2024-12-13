/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:39:17 by antauber          #+#    #+#             */
/*   Updated: 2024/12/13 18:11:57 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	child_process(t_data *data, char *argv, char **env, int i_cmd, int *pipefd)
{
	char	**params;
	int		size;

	if (i_cmd == 0) // si premiere commande
	{
		if (dup2(data->child.fd_infile, STDIN_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2);
		close (data->child.fd_outfile);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else if (i_cmd == data->n_cmdp - 1) // si derniere commande
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2); 
		if (dup2(data->child.fd_outfile, STDOUT_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2); 
		close(data->child.fd_outfile);
		close(pipefd[0]);
		close(pipefd[1]);

	}
	else	// commande intermdiaires // ! not in manda
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			clean_data(data, 1, ERR_DUP2);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	data->only_cmd = rm_option_n_spaces(data->cmdp[i_cmd]);
	if (data->only_cmd == NULL)
		clean_data(data, 2, ERR_MALL);
	params = ft_split(argv, ' ');
	size = ft_count_words(argv, ' ');
	if (params == NULL)
		clean_data(data, 2, ERR_MALL);
	// ! close all opened fds
	if (execve(data->only_cmd, params, env) == -1)
	{
		ft_free_tabstr(params, size);
		params = NULL;
		clean_data(data, 1, ERR_CMD);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	pid_t	pid;
	int		i;
	int		pipefd[2];
	
	i = 2;
	init_data(&data, argc, argv);
	parsing(argc, argv, env, &data);
	ft_print_tabstr(data.cmdp, GREEN);
	if (pipe(pipefd) == -1)
		ft_error(1, ERR_PIPE);
	while (i < argc - 1)
	{
		pid = fork();
		if (pid == -1)
			clean_data(&data, 1, ERR_FORK);
		else if (pid == 0)
		{
			child_process(&data, argv[i], env, (i - 2), pipefd);
		}
		else
		{
			ft_printf(1, "Parent\n");
			close(pipefd[0]);
			close(pipefd[1]);
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	clean_data(&data, 0, NULL);
	return (0);
}
