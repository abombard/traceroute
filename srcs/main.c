/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 15:06:12 by abombard          #+#    #+#             */
/*   Updated: 2017/05/09 14:03:32 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

int		main(int argc, char **argv)
{
	t_context		context;

	if (getuid() != 0)
	{
		fprintf(stderr, PROGNAME ": Permission denied\n");
		exit(EXIT_FAILURE);
	}
	context = init(argc, argv);
	printf("traceroute to %s (%s), %d hops max, %d byte packets.\n",
		context.targetnamestr, context.targetaddrstr,
		context.hops, 60);
	traceroute(&context);
	return (0);
}
