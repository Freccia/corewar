/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:00:00 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/26 16:32:50 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void cw_vm_insert(t_player** head, t_player* new)
{
    t_player* curr;

    if (*head == NULL || (*head)->id >= new->id)
    {
        new->next = *head;
        *head = new;
    }
    else
    {
        curr = *head;
        while (curr->next && curr->next->id < new->id)
        {
            curr = curr->next;
        }
        new->next = curr->next;
        curr->next = new;
    }
}

void cw_vm_insert_sort(t_player **head)
{
	t_player *sort;
    t_player *curr;
    t_player *next;

	sort = NULL;
	curr = *head;
    while (curr != NULL)
    {
		next = curr->next;
        cw_vm_insert(&sort, curr);
        curr = next;
    }
    *head = sort;
}
