/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:57:40 by abombard          #+#    #+#             */
/*   Updated: 2017/05/06 15:00:43 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static int		init_packet(u_char *packet, t_context *context)
{
	struct ip		*ip;
	struct udphdr	*udp;
	int				*seq;
	int				*ttl;
	struct timeval	*tp;
	int				packlen;

	packlen = sizeof(struct ip)
			+ sizeof(struct udphdr)
			+ sizeof(int)
			+ sizeof(int)
			+ sizeof(struct timeval);
	ip = (struct ip *)packet;
	udp = (struct udphdr *)(ip + 1);
	seq = (int *)(udp + 1);
	ttl = (int *)(seq + 1);
	tp = (struct timeval *)(ttl + 1);
	ip->ip_v = 4;
	ip->ip_hl = sizeof(*ip) >> 2;
	//ip->ip_src = 0;
	ip->ip_dst = ((struct sockaddr_in *)&context->targetaddr)->sin_addr;
	ip->ip_p = SOL_UDP;
	ip->ip_ttl = context->ttl;
	ip->ip_len = htons(packlen);
	udp->uh_sport = htons(context->ident);
	udp->uh_dport = htons(context->port + context->seq);
	udp->uh_ulen = htons((u_short)(packlen - sizeof(*ip)));
	udp->uh_sum = 0;
	*seq = context->seq;
	*ttl = context->ttl;
	gettimeofday(tp, 0);

	return (packlen);
}

int				send_packet(t_context *context)
{
	u_char			packet[MAXPACKET];
	int				packlen;
	int				nbytes;

	ft_bzero(packet, sizeof(packet));
	packlen = init_packet(packet, context);
	nbytes = sendto(context->sndsfd, (char *)packet, packlen, 0,
			(struct sockaddr *)&context->targetaddr, context->targetaddrlen);
	if (nbytes < 0)
	{
		perror(PROGNAME ": sendto");
		exit(EXIT_FAILURE);
	}
	if (nbytes != packlen)
		fprintf(stderr, PROGNAME ": sendto: %d != %d\n", nbytes, packlen);
	return (nbytes == packlen);
}
