#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "Libft/libft.h"

char *ft_get_exec(char **env, char *cmd);
void ft_child(char **argv, int *pipe_fd, char **env);
void ft_parent(char **argv, int *pipe_fd, char **env);

#endif