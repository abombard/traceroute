/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethostaddrstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:49:58 by abombard          #+#    #+#             */
/*   Updated: 2017/05/17 16:33:18 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static const char	*gethostaddrv4(
		const struct sockaddr *sockaddr, char *hostaddr, size_t size_max)
{
	struct sockaddr_in	*sockaddr_in;
	const char			*success;

	sockaddr_in = (struct sockaddr_in *)sockaddr;
	success = inet_ntop(AF_INET,
						(void *)&sockaddr_in->sin_addr,
						hostaddr, size_max);
	return (success);
}

static const char	*gethostaddrv6(
		const struct sockaddr *sockaddr, char *hostaddr, size_t size_max)
{
	struct sockaddr_in6	*sockaddr_in6;
	const char			*success;

	sockaddr_in6 = (struct sockaddr_in6 *)sockaddr;
	success = inet_ntop(AF_INET6, (void *)&sockaddr_in6->sin6_addr,
			hostaddr, size_max);
	return (success);
}

extern void			gethostaddrstr(
		const struct sockaddr *sockaddr,
		char *hostaddr, size_t size_max)
{
	if (sockaddr->sa_family == AF_INET)
		gethostaddrv4(sockaddr, hostaddr, size_max);
	else if (sockaddr->sa_family == AF_INET6)
		gethostaddrv6(sockaddr, hostaddr, size_max);
	else
	{
		fprintf(stderr, PROGNAME ": gethostaddr: ai_family %d is not handled\n",
				sockaddr->sa_family);
		exit(EXIT_FAILURE);
	}
}
