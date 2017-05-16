/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_triptime.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 14:01:57 by abombard          #+#    #+#             */
/*   Updated: 2017/05/09 14:01:58 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

long	round_triptime(struct timeval *tp)
{
	struct timeval	tv;
	long			triptime;

	(void)gettimeofday(&tv, (struct timezone *)0);
	tvsub(&tv, tp);
	triptime = tv.tv_sec * 10000000 + tv.tv_usec;
	return (triptime);
}
