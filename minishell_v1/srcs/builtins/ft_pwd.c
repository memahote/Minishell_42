/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:20:18 by memahote          #+#    #+#             */
/*   Updated: 2024/01/31 18:01:07 by memahote         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_pwd(void)
{
	char	*path_dir;

	path_dir = NULL;
	path_dir = getcwd(path_dir, PATH_MAX);
	if (path_dir == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", path_dir);
	free(path_dir);
	return (EXIT_SUCCESS);
}
