/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:44:32 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/23 15:45:22 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Esta funcao utiliza a funcao getcwd() da biblioteca unistd.h.
Essa funcao permite obter o diretório de trabalho atual. Ela recebe 
como argumentos o buffer cwd para armazenar o diretório atual 
e o tamanho máximo do buffer. cwd - current working directory
 */
void	__exec_pwd(char **env, t_list **lst)
{
    char cwd[PATH_MAX];

    (void)env;
	(void)lst;
	close_fds(lst, 1);
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
        printf("Current directory: %s\n", cwd);
	else {
        perror("Error getting current directory");
        exit(0);
    }
}

//Theory

//The PATH_MAX constant is defined in the <limits.h> header 
//file and represents the maximum length of a file path 
//(including the null terminator) on a particular system.