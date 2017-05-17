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

struct timeval	round_triptime(struct timeval *tp, struct timezone *tz)
{
	struct timeval	tv;

	gettimeofday(&tv, tz);
	tvsub(&tv, tp);
	return (tv);
}
