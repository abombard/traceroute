#include "traceroute.h"

void	unpack(u_char *packet,
		struct ip **ip, struct icmp **icmp, struct udphdr **udp)
{
	struct ip	*hip;

	*ip = (struct ip *)packet;
	*icmp = (struct icmp *)(packet + ((*ip)->ip_hl << 2));
	hip = &(*icmp)->icmp_ip;
	*udp = (struct udphdr *)((void *)hip + (hip->ip_hl << 2));

	/*
	if (icmp->type == ICMP_TIME_EXCEEDED || icmp->type == ICMP_ECHOREPLY)
		print_triptime(icmp, packlen, ttl, context);
	else if (context->verbose)
		fprintf(stderr, "\n%d bytes from %s (%s): type=%d, code=%d\n", packlen,
			context->hostname, context->hostaddr, icmp->type, icmp->code);
			*/
}

int		wait_for_reply(int sfd,
		u_char *packet, size_t maxpacket,
		struct sockaddr *from)
{
	int			packlen;
	socklen_t	fromlen;

	if (!rsock_ready(sfd))
		return (0);
	fromlen = sizeof(*from);
	packlen = recvfrom(sfd,
		(char *)packet, maxpacket, 0,
		from, &fromlen);
	if (packlen < 0)
	{
		perror(PROGNAME ": recvfrom");
		exit(EXIT_FAILURE);
	}
	return (packlen);
}

int		recv_packet(t_context *context)
{
	u_char					packet[MAXPACKET];
	int						packlen;
	struct sockaddr			from;
	int						loop = 0;

	packlen = 0;
	while ((packlen = wait_for_reply(context->sfd,
					packet, sizeof(packet), &from)))
	{
		struct ip		*ip;
		struct icmp		*icmp;
		struct udphdr	*udp;

		unpack(packet, &ip, &icmp, &udp);
		packlen -= ip->ip_hl << 2;
		if ((unsigned long)packlen < ICMP_MINLEN)
		{
			fprintf(stderr, PROGNAME ": packet too short (%d bytes)\n", packlen);
			return (0);
		}
		if (udp->uh_sport != htons(context->ident) ||
			udp->uh_dport != htons(context->port + context->seq))
		{
			fprintf(stderr,
					"icmp type=%d code=%d udp sport %d expect %d dport %d expect %d\nloop %d\n",
					icmp->icmp_type, icmp->icmp_code,
					udp->uh_sport, htons(context->ident),
					udp->uh_dport, htons(context->port + context->seq),
					loop ++);

			continue ;
		}

		if (ft_memcmp(&context->fromaddr, &from, sizeof(from)))
		{
			gethostaddrstr(&from, context->fromaddrstr, sizeof(context->fromaddrstr));
			gethostnamestr(&from, context->fromnamestr, sizeof(context->fromnamestr));

			context->fromaddr = from;

			printf(" %s (%s)", context->fromnamestr, context->fromaddrstr);
		}

		struct timeval	triptime;

		triptime = round_triptime(&context->tv, &context->tz);
		printf("  %ld.%d ms", triptime.tv_sec * 1000 + triptime.tv_usec / 1000, triptime.tv_usec % 1000);

		if (icmp->icmp_type == ICMP_UNREACH)
			context->reachedtarget = 1;

		break ;
	}

	if (packlen == 0)
	{
		printf(" *");
	}

	return (1);
}
