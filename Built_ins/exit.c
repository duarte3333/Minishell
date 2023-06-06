/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:57:12 by duarte33          #+#    #+#             */
/*   Updated: 2023/06/06 19:07:31 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Esta funcao verifica se uma str tem apenas digitos */
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

/* Esta funcao verifica se o exit code ultrapassa do long long max */
int	exit_overflow(t_list **lst)
{
	int	i;

	i = 0;
	if ((*lst)->content[1] && (*lst)->content[1][0])
		i = 0 + ((*lst)->content[1][0] == '-' || (*lst)->content[1][0] == '+');
	if ((*lst)->content[1] && (ft_strlen((*lst)->content[1] + i) > 19 || \
		(i && ft_strlen((*lst)->content[1]) == 20 && \
		ft_strncmp("-9223372036854775808", (*lst)->content[1], 20) < 0) || \
		(!i && ft_strlen((*lst)->content[1]) == 19 && \
		ft_strncmp("9223372036854775807", (*lst)->content[1], 19) < 0)))
	{
		write(2, "minishell: exit: ", 17);
		write(2, (*lst)->content[1], ft_strlen((*lst)->content[1]));
		write(2, ": numeric argument required\n", 29);
		return (1);
	}
	return (0);
}

void	is_numeric_arg(t_list **lst)
{
	g_data.status = 2;
	write(2, "minishell: exit: ", 17);
	write(2, (*lst)->content[1], ft_strlen((*lst)->content[1]));
	write(2, ": numeric argument required\n", 29);
}

/* Esta funcao replica o comportamento do exit, um comando built in
do bash.*/
void	__exec_exit(t_list **lst)
{
	int	nb;

	write(2, "exit\n", 5);
	if (exit_overflow(lst))
		g_data.status = 2;
	else if ((*lst)->content[1] && (*lst)->content[2])
	{
		g_data.status = 1;
		write(2, "minishell: exit: too many arguments\n", 37);
	}
	else if ((*lst)->content[1] && ft_str_is_num((*lst)->content[1]) == 0)
		is_numeric_arg(lst);
	else if ((*lst)->content[1])
	{
		nb = ft_atoi((*lst)->content[1]);
		if (nb >= 256)
			nb -= 256;
		g_data.status = nb;
	}
	ft_free_list(list);
	ft_free_env(&g_data.env);
	ft_free_list(lst);
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