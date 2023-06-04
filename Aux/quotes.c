/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:06:19 by duarte33          #+#    #+#             */
/*   Updated: 2023/06/03 14:23:31 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_quotes(char **input)
{
	int	k;

	k = -1;
	while (input[++k])
	{
		if (ft_strchr(input[k], '\'') || ft_strchr(input[k], '\"'))
			delete_quotes_string(&input[k], 0);
	}
}

void	treat_quotes(char *input, int i, int *flag)
{
	char	c;

	c = input[i];
	*flag = c;
	while (input[++i])
	{
		if (c == input[i])
			return ;
	}
	syntax_error(&c, input, 1);
}
