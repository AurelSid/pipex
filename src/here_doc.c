/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:50:46 by roko              #+#    #+#             */
/*   Updated: 2024/06/28 14:53:19 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_gnl_to_fd(char **argv, int *pipe_fd)
{
	char	*line;
	char	*limiter;

	close(pipe_fd[0]);
	limiter = argv[2];
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
		{
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			exit(0);
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	ft_limiter_exec(char **argv)
{
	int		pipe_fd[2];
	pid_t	process_id;

	process_id = 0;
	if (pipe(pipe_fd) == -1)
		exit(0);
	process_id = fork();
	if (process_id == -1)
		exit(0);
	else if (process_id == 0)
	{
		ft_gnl_to_fd(argv, pipe_fd);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		wait(NULL);
	}
}
