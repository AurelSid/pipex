/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roko <roko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:03:54 by roko              #+#    #+#             */
/*   Updated: 2024/06/22 20:38:14 by roko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void ft_exec_pipe(char *argv, char **env)
{
    int pipe_fd[2]; // init les deux fd de la pipe
    pid_t process_id;

    if (pipe(pipe_fd) == -1)
        exit(0);
    process_id = fork();
    if (process_id == 0) // si on se trouve dans literation fork child
    {
        dup2(pipe_fd[1], 1);    // stocker dans le write
        close(pipe_fd[0]);      // fermer le read
        ft_get_exec(env, argv); // executer la cmd
    }
    else // si la cmd est finie (retour dans le parent)
    {
        close(pipe_fd[1]);   // fermer la pipe de write
        dup2(pipe_fd[0], 0); // donner le read au stdout pour la lecture suivante
    }
}

int main(int argc, char **argv, char **env)
{
    int infd;
    int outfd;
    int i;

    i = 2;
    if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
    {
        i++;
        if (argc < 6)
            return(0);
        outfd = open(argv[argc - 1], O_APPEND);//ouverture en APPEND pour sassurer que >> rajouter et ne reecrit pas.01
        ft_limiter_exec(argv);
    }
    else
    {
        infd = open(argv[1], O_RDONLY);
        outfd = open(argv[argc - 1], O_WRONLY);
        dup2(infd, 0); // dup the txt de debut pour la 1ere cmd , ensuite le 0 fera ref au read du pipe precedent;
    }
    while (i < argc - 2) // (argc - les deux fichier txt et la derniere cmd )
    {
        ft_exec_pipe(argv[i], env);
        i++;
    }
    dup2(outfd, 1);// Fini par remplacer le output par le txt de sortie et execv la derniere cmd
    ft_get_exec(env, argv[argc - 2]); // argc -12 ou i
    return (0);
}
