/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roko <roko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:03:54 by roko              #+#    #+#             */
/*   Updated: 2024/06/21 16:30:09 by roko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(int argc, char **argv, char **env)
{
    pid_t process_id;
    const char *output_path;
    const char *input_path;
    // const char *path_env;
    int fd[2];

    input_path = argv[1];
    output_path = argv[argc - 1];
    if (access(input_path, F_OK | W_OK | R_OK) == 0 && access(output_path, F_OK | W_OK | R_OK) == 0)
        (printf("--  files ok  --\n"));
    else
        (printf("missing file\n"));

    if (pipe(fd) == -1)
    {
        printf("err opening the pipe");
    }

    process_id = fork();
    if (process_id == -1)
        return (0);
    if (process_id == 0)
    {
        ft_child(argv, fd, env);
    }
    ft_parent(argv, fd, env);

    return (0);
}