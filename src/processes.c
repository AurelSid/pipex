/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roko <roko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:34:29 by roko              #+#    #+#             */
/*   Updated: 2024/06/21 12:34:29 by roko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
void ft_child(char **argv, int *pipe_fd, char **env)
{
    int infd;

    infd = open(argv[1], O_RDONLY);
    dup2(infd, 0);
    dup2(pipe_fd[1], 1);
    close(pipe_fd[0]);

    ft_get_exec(env, argv[2]);
}
void ft_parent(char **argv, int *pipe_fd, char **env)
{
    int outfd;

    outfd = open(argv[4], O_WRONLY);

    dup2(outfd, 1);
    dup2(pipe_fd[0], 0);
    close(pipe_fd[1]);

    ft_get_exec(env, argv[3]);
}
