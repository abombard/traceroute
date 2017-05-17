/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:55:42 by abombard          #+#    #+#             */
/*   Updated: 2017/05/17 16:37:09 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEROUTE_H
# define TRACEROUTE_H

# include "libft.h"

# include <sys/socket.h>
# include <sys/time.h>
# include <sys/signal.h>

# include <netinet/ip.h>
# include <netinet/udp.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>

/*
** # define DEBUG
*/

# define PROGNAME		"ft_traceroute"

# define ADDRFAMILY		AF_INET
# define MAXADDRSIZE	64

# define MAXPACKET		(65536 - 60 - 8)
# define MAXWAIT		50000

typedef struct			s_context
{
	char				targetnamestr[MAXADDRSIZE];
	char				targetaddrstr[MAXADDRSIZE];

	struct sockaddr		targetaddr;
	socklen_t			targetaddrlen;

	char				fromnamestr[MAXADDRSIZE];
	char				fromaddrstr[MAXADDRSIZE];

	struct sockaddr		fromaddr;
	socklen_t			fromaddrlen;

	int					port;

	int					sndsfd;
	int					sfd;

	int					ident;

	int					verbose;

	int					hops;
	int					ttl;

	int					npackets;
	int					seq;

	struct timeval		tv;

	int					reachedtarget;

}						t_context;

/*
** init
*/
void					usage(char *prog);
int						getopts(int argc, char **argv, t_context *context);

/*
** checksum
*/
uint16_t				compute_checksum(uint8_t *buf, unsigned int size);

/*
** tvsub
*/
void					tvsub(struct timeval *out, struct timeval *in);

/*
** traceroute
*/
t_context				init(int argc, char **argv);

void					traceroute(t_context *context);

void					newsock(t_context *context);

void					gethostaddrstr(
							const struct sockaddr *sockaddr,
							char *hostaddr, size_t size_max);
void					gethostnamestr(struct sockaddr *sockaddr,
							char *hostname, size_t size_max);

int						wsock_ready(int sfd);
int						rsock_ready(int sfd);

int						send_packet(t_context *context);
int						recv_packet(t_context *context);

struct timeval			round_triptime(struct timeval *tp);

void					print_triptime(
		struct icmp *icmp, t_context *context);

void					ip_dump(struct ip *ip);

#endif
