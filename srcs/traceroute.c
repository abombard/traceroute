#include "traceroute.h"

void	setsock_ttl(int sndsfd, int ttl)
{
	if (setsockopt(sndsfd, IPPROTO_IP, IP_TTL,
				&ttl, sizeof(ttl)))
	{
		perror(PROGNAME ": setsockopt");
		exit(EXIT_FAILURE);
	}
}

void	traceroute(t_context *context)
{
	newsock(context);
	context->reachedtarget = 0;
	context->ttl = 1;
	while (context->ttl <= context->hops && !context->reachedtarget)
	{
		//setsock_ttl(context->sndsfd, context->ttl);
		printf("%2d ", context->ttl);
		context->npackets = 0;
		while (context->npackets < 3)
		{
			send_packet(context);

			gettimeofday(&context->tvbegin,
				(struct timezone *)0);

			recv_packet(context);

			context->seq += 1;
			context->npackets += 1;
		}
		printf("\n");
		context->ttl += 1;
	}
	close(context->sndsfd);
	close(context->sfd);
}
