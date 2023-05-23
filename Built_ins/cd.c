#include "../minishell.h"

void		print_path(char *path)
{
	//char	*parsed_home;

	//parsed_home = get_env_var("HOME");
	//printf("%s\n", parsed_home);
}

int		two_args(t_list *lst)
{
	if (lst->content[2])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
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

	if (!chdir(path))
	{
		if (print)
		{
			//printf_path(path);
			printf("%s\n", path);
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
	//char	*path_home;

	//path_home = get_env_var("HOME");
	if (!(*lst)->content[1] && change_dir("/nfs/homes/mtiago-s", 0))
		return ;
	if (two_args(*lst))
		return ;
	else
	{
		if (!ft_strcmp((*lst)->content[1], "--") && change_dir("/nfs/homes/mtiago-s", 0))
			return ;
		else if (((*lst)->content[1][0] == '-') && !(*lst)->content[1][2])
		{
			change_dir("/home/duarte33/42School/minishell", 1);
			//change_dir(get_env_var("OLDPWD"), 1);
			return ;
		}
		change_dir((*lst)->content[1], 0);
	}
	return ;
}
