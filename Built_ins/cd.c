/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:44:22 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/30 17:14:52 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_path(char *path)
{
	//char	*parsed_home;
	(void) path;
	//parsed_home = search_env_var("HOME");
	//printf("%s\n", parsed_home);
}

// R_OK: Verifica se o arquivo pode ser lido.
// W_OK: Verifica se o arquivo pode ser escrito.
// X_OK: Verifica se o arquivo pode ser executado.
// F_OK: Verifica se o arquivo existe. 

/* Esta funcao muda o diretorio e atualiza a variavel de
ambiente OLDPWD caso seja necessario. Em caso de sucesso chdir retorna 0 */
int	change_dir(char *path, int print)
{
	char	buff[PATH_MAX];
	t_env	*lst_env_export;

	if (!chdir(path))
	{
		if (print)
		{
			//printf_path(path);
			printf("%s\n", path);
		}
		lst_env_export = env_lst_search("OLDPWD");
		if (lst_env_export)
		{
		 	free(lst_env_export->content);
		 	lst_env_export->content = getcwd(buff, PATH_MAX);
		}
		//set_var("OLDPWD", getcwd(buff, PATH_MAX));
		//Falta aqui mudar a variavel OLDPWD no env com getcwd
	}
	else
	{
		printf("cd: ");
		if (access(path, F_OK) == -1)
			printf("no such file or directory: ");
		else if (access(path, R_OK | W_OK | X_OK) == -1)
			printf("permission denied: ");
		else
			printf("not a directory: ");
		printf("%s\n", path);
	}
	return (1);
}

/* Esta funcao replica o comando cd apenas com path relativo ou absoluto.
   Existem os seguintes caos: "cd" ; "cd --" ; "cd -" ; "cd <algum caminho>" */
void	__exec_cd(char **env, t_list **lst)
{
	(void)env;
	char	*path_home;
	char	**env_char;

	go_head(lst);
	if (ft_matrixlen((*lst)->content) > 2)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	env_char = ft_env_lst_to_arr(g_data.env);
	path_home = search_env(env_char, "HOME");
	if (!(*lst)->content[1] && change_dir(path_home, 0))
	{
		ft_free_matrix(&env_char);
		return ;
	}
	else
	{
		if (!ft_strcmp((*lst)->content[1], "--") && change_dir(path_home, 0))
		{
			ft_free_matrix(&env_char);
			return ;
		}
		else if ((*lst)->content[1][0] == '-')
		{
			printf("[str] %s \n", search_env(env_char, "OLDPWD"));
			change_dir(search_env(env_char, "OLDPWD"), 1);
			ft_free_matrix(&env_char);
			return ;
		}
		change_dir((*lst)->content[1], 0);
	}
	ft_free_matrix(&env_char);
	return ;
}