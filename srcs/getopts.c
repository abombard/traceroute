/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:53:03 by abombard          #+#    #+#             */
/*   Updated: 2017/05/06 14:54:51 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"
#include "libft.h"

#include <stdlib.h>

static char	ft_getopt(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] != '-')
		return (0);
	if (ft_strlen(arg) != 2)
		return (0);
	return (arg[1]);
}

static int	is_digit(char *arg)
{
	if (!arg)
		return (0);
	return (ft_atoi(arg) > 0);
}

int			getopts(int argc, char **argv, t_context *context)
{
	char	c;
	int		i;

	i = 0;
	while ((c = ft_getopt(argv[++i])))
	{
		if (c == 'v')
			context->verbose = 1;
		else if (c == 'p' && is_digit(argv[i + 1]))
			context->port = ft_atoi(argv[i++ + 1]);
		else
		{
			usage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (i != argc - 1)
	{
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	ft_strncpy(context->targetnamestr, argv[i], sizeof(context->targetnamestr));
	return (0);
}
