#include "../minishell.h"

int	ft_str_is_num(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	__exec_exit(char **env, t_list **lst)
{
	(void)env;
	int	nb;
	int i;

	i = 0 + ((*lst)->content[1][0] == '-' || (*lst)->content[1][0] == '+');
	write(2, "exit :) 🏊\n", 14);
	if (ft_strlen((*lst)->content[1] + i) > 19 || \
		(i && ft_strlen((*lst)->content[1]) == 20 && \
		ft_strncmp("-9223372036854775808", (*lst)->content[1], 20) < 0) || \
		(!i && ft_strlen((*lst)->content[1]) == 19 && \
		ft_strncmp("9223372036854775807", (*lst)->content[1], 19) < 0))
	{
		g_data.status = 2;
		write(2, "minishell: exit: ", 17);
		write(2, (*lst)->content[1], ft_strlen((*lst)->content[1]));
		write(2, ": numeric argument required\n", 29);
	}
	else if ((*lst)->content[1] && (*lst)->content[2])
	{
		g_data.status = 1;
		write(2, "minishell: exit: too many arguments", 36);
	}
	else if ((*lst)->content[1] && ft_str_is_num((*lst)->content[1]) == 0)
	{
		g_data.status = 2;
		write(2, "minishell: exit: ", 17);
		write(2, (*lst)->content[1], ft_strlen((*lst)->content[1]));
		write(2, ": numeric argument required\n", 29);
	}
	else if ((*lst)->content[1])
	{
		nb = ft_atoi((*lst)->content[1]);
		if (nb >= 256)
			nb -= 256;
		g_data.status = nb;
	}
	//printf("EXIT_STATUS: %i\n", g_data.status);
	ft_free_env(&g_data.env);
	exit(g_data.status);
}
// 0: Indica que o comando foi executado com sucesso, sem erros.
// 1: Indica um erro genérico ou não especificado.
// 2: Indica um erro de sintaxe no comando.
// 126: Indica que o comando não é executável.
// 127: Indica que o comando não foi encontrado.
// 128: Indica um erro de interrupção de script 
//     (por exemplo, quando o script é interrompido pelo sinal SIGINT).
// 130: Indica que o script foi interrompido manualmente 
//     (por exemplo, quando o usuário pressiona Ctrl+C).
// 255: É o valor máximo permitido para um código de saída. 
//      Valores acima de 255 geralmente são truncados para se 
//      encaixar nesse intervalo.