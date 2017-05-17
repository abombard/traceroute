/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:36:51 by abombard          #+#    #+#             */
/*   Updated: 2017/05/17 16:36:54 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

void	traceroute(t_context *context)
{
	context->reachedtarget = 0;
	context->ttl = 1;
	while (context->ttl <= context->hops && !context->reachedtarget)
	{
		printf("%2d ", context->ttl);
		context->npackets = 0;
		while (context->npackets < 3)
		{
			send_packet(context);
			gettimeofday(&context->tv, &context->tz);
			recv_packet(context);
			context->seq += 1;
			context->npackets += 1;
		}
		printf("\n");
		context->ttl += 1;
	}
}
