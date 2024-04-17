/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:21:45 by memahote          #+#    #+#             */
/*   Updated: 2023/12/09 16:21:45 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ifclosed(char *line, int index, int *nb_quote, int quote)
{
	int	i;

	i = index + 1;
	*nb_quote += 1;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		*nb_quote += 1;
	return (i - index);
}

int	check_quote_input(char *line)
{
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	dquote = 0;
	squote = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			i += check_ifclosed(line, i, &dquote, '\"');
		else if (line[i] == '\'')
			i += check_ifclosed(line, i, &squote, '\'');
		i++;
	}
	if ((dquote > 0 && dquote % 2 != 0) || (squote > 0 && squote % 2 != 0))
		return (0);
	return (1);
}
