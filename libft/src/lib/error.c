/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib/error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:14 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/14 01:25:17 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#ifndef EQFULL
# define EQFULL 106
#endif

int	ft_error(int rno, int eno)
{
	if (eno <= 0 || eno > EQFULL)
	{
		errno = EINVAL;
		return (-1);
	}
	errno = eno;
	return (rno);
}
