/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 15:00:58 by abombard          #+#    #+#             */
/*   Updated: 2017/05/06 15:05:59 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

extern t_context	init(int argc, char **argv)
{
	t_context			context;

	ft_bzero(&context, sizeof(context));
	context.ident = getpid() & 0xffff;
	context.hops = 30;
	context.ttl = 1;
	context.seq = 1;
	context.port = 32768 + 666;
	getopts(argc, argv, &context);
	return (context);
}
