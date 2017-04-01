#include "traceroute.h"

#ifdef DEBUG

void	ip_dump(struct iphdr *ip)
{
	printf("ip v %d size %d\n", ip->version, ip->ihl << 2);
	printf("tos %d tot_len %d id %d frag_off %d ttl %d protocol %d check %d\n",
			ip->tos, ip->tot_len, ip->id, ip->frag_off, ip->ttl, ip->protocol, ip->check);
	printf("saddr %s daddr %s\n", inet_ntoa(*(struct in_addr *)&ip->saddr), inet_ntoa(*(struct in_addr *)&ip->daddr));
}

#endif

void	sockaddr_to_string(struct sockaddr_storage *addr, char *s, size_t size)
{
	const char	*res = NULL;

	if (addr->ss_family == AF_INET)
	{
		struct sockaddr_in	*sockaddr_in;

		sockaddr_in = (struct sockaddr_in *)addr;
		res = inet_ntop(addr->ss_family, &sockaddr_in->sin_addr, s, size);
	}
	else if (addr->ss_family == AF_INET6)
	{
		struct sockaddr_in6	*sockaddr_in6;

		sockaddr_in6 = (struct sockaddr_in6 *)addr;
		res = inet_ntop(addr->ss_family, &sockaddr_in6->sin6_addr, s, size);
	}
	else
	{
		fprintf(stderr, PROGNAME ": addr->ss_family %d\n", addr->ss_family);
		exit(EXIT_FAILURE);
	}
	if (!res)
	{
		perror(PROGNAME ": inet_ntop");
		exit(EXIT_FAILURE);
	}
}

typedef struct	s_packet
{
	struct iphdr	ip;
	struct udphdr	udp;
	unsigned char	seq;
	unsigned char	ttl;
	struct timeval	tv;
}				t_packet;

void	ping(t_context *context, int seq, int ttl)
{
	t_packet		packet;
	int				ident;

	ident = getpid() & 0xffff;

	packet.ip.version = 4;
	packet.ip.ihl = sizeof(packet.ip) >> 2;
	packet.ip.tos = 0;
	packet.ip.tot_len = sizeof(packet);
	packet.ip.id = ident + seq;
	packet.ip.frag_off = 0;
	packet.ip.ttl = ttl;
	packet.ip.protocol = IPPROTO_UDP;
	/* packet.ip.saddr = ; set automatically ? */
	packet.ip.daddr = ((struct sockaddr_in *)&context->sockaddr)->sin_addr.s_addr;

	packet.udp.source = htons(ident);
	packet.udp.dest = htons(PORT + seq);
	packet.udp.len = htons(sizeof(packet));
	packet.udp.check = 0;

	packet.seq = seq;
	packet.ttl = ttl;

	(void)gettimeofday(&packet.tv, (struct timezone *)0);

	int	nbytes = sendto(context->sockfd, &packet, sizeof(packet), 0,
			(struct sockaddr *)&context->sockaddr, context->sockaddrlen);
	if (nbytes < 0)
	{
		perror(PROGNAME ": sendto");
		exit(EXIT_FAILURE);
	}
	if (nbytes != sizeof(packet))
	{
		fprintf(stderr, PROGNAME ": sendto: Couldnt send the whole packet %d!=%lu\n", nbytes, sizeof(packet));
	}
}

void	pong(t_context *context, int *type, struct sockaddr_storage *from)
{
	char					packet[MAXPACKET];
	socklen_t				fromlen;
	int						nbytes;

	fromlen = sizeof(from);
	nbytes = recvfrom(context->sockfd, packet, sizeof(packet), 0,
					(struct sockaddr *)from, &fromlen);
	if (nbytes < 0)
	{
		perror(PROGNAME ": recvfrom");
		exit(EXIT_FAILURE);
	}

	struct iphdr	*ip;
	struct icmphdr	*icmp;
	int				hlen;

	ip = (struct iphdr *)packet;
	hlen = ip->ihl << 2;
	if ((unsigned long)nbytes < hlen + sizeof(struct icmphdr) + sizeof(struct timeval))
	{
		fprintf(stderr, PROGNAME ": recvfrom: nbytes %d < %lu\n", nbytes, sizeof(struct iphdr) + sizeof(struct icmphdr));
	}

	icmp = (struct icmphdr *)(packet + hlen);

	char	fromstr[MAXADDRSIZE];
	sockaddr_to_string(from, fromstr, sizeof(fromstr));

	printf("%d bytes from %s: ", nbytes, fromstr);
	printf("ip version %d ttl %d protocol %d\n", ip->version, ip->ttl, ip->protocol);

	printf("type %d code %d", icmp->type, icmp->code);
	printf("\n");

	*type = icmp->type;
}

void	traceroute(t_context *context)
{
	int				ttl;
	int				seq;

	seq = 0;
	ttl = 1;
	while (ttl <= context->hops)
	{
		printf("%d: ", ttl);

		int							type;
		struct sockaddr_storage		from;
		int						i;

		i = 0;
		while (i < context->req_per_hop)
		{
			struct timeval			t1, t2;

			(void)gettimeofday(&t1, (struct timezone *)0);

			fprintf(stderr, "ping\n");
			ping(context, seq, ttl);

			fprintf(stderr, "pong\n");

			pong(context, &type, &from);

			(void)gettimeofday(&t2, (struct timezone *)0);

			i += 1;
			seq += 1;
		}

		char	addr[MAXADDRSIZE];

		sockaddr_to_string(&from, addr, sizeof(addr));

		printf("%s\n", addr);

		ttl += 1;
	}

}

int		main(int argc, char **argv)
{
	t_context	context;

	// init
	ft_bzero(&context, sizeof(context));
	context.hops = 30;
	context.req_per_hop = 3;
	getopts(argc, argv, &context);

	struct addrinfo		*res;
	struct addrinfo		hints;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_UDP;

	int err = getaddrinfo(context.hostname, NULL, &hints, &res);
	if (err)
	{
		fprintf(stderr, PROGNAME ": getaddrinfo: %s\n", gai_strerror(err));
		exit(EXIT_FAILURE);
	}

	context.sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (context.sockfd == -1)
	{
		perror(PROGNAME ": socket");
		exit(EXIT_FAILURE);
	}

	ft_memcpy(&context.sockaddr, res->ai_addr, res->ai_addrlen);
	context.sockaddrlen = res->ai_addrlen;

	freeaddrinfo(res);


	(void)printf("traceroute to %s: %d hops max, %d bytes packets\n",
		context.hostname, context.hops, DATALEN);


	traceroute(&context);

	return (0);
}
