/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:44:22 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/04 23:36:25 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// R_OK: Verifica se o arquivo pode ser lido.
// W_OK: Verifica se o arquivo pode ser escrito.
// X_OK: Verifica se o arquivo pode ser executado.
// F_OK: Verifica se o arquivo existe. 

/* Esta funcao muda o diretorio e atualiza a variavel de
ambiente OLDPWD caso seja necessario. Em caso de sucesso chdir retorna 0 */
int	change_dir(char *path)
{
	if (!chdir(path))
		g_data.status = 0;
	else
	{
		if (access(path, F_OK) == -1)
			write(2, "minishell: cd: no such file or directory: ", 43);
		else if (access(path, R_OK | W_OK | X_OK) == -1)
			write(2, "minishell: cd: permission denied: ", 35);
		else
			write(2, "minishell: cd: not a directory: ", 33);
		write(2, path, ft_strlen(path));
		g_data.status = 1;
	}
	return (1);
}

void	finish_cd(char **env_char)
{
	ft_free_matrix(&env_char);
	g_data.status = 0;
	return ;
}

/* Esta funcao replica o comando cd apenas com path relativo ou absoluto.
   Existem os seguintes caos: "cd" ; "cd --" ; "cd -" ; "cd <algum caminho>" */
void	__exec_cd(t_list **lst)
{
	char	*path_home;
	char	**env_char;

	go_head(lst);
	if (ft_matrixlen((*lst)->content) > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		g_data.status = 1;
		return ;
	}
	env_char = ft_env_lst_to_arr(g_data.env);
	path_home = search_env(env_char, "HOME");
	if (!(*lst)->content[1] && change_dir(path_home))
		return (finish_cd(env_char));
	else
	{
		if (!ft_strcmp((*lst)->content[1], "--") && change_dir(path_home))
			return (finish_cd(env_char));
		change_dir((*lst)->content[1]);
	}
	ft_free_matrix(&env_char);
	return ;
}
