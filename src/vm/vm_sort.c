/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:30:57 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/16 12:36:16 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void cw_vm_insert(t_champ** head, t_champ* new)
{
    t_champ* current;

    if (*head == NULL || (*head)->id >= new->id)
    {
        new->next = *head;
        *head = new;
    }
    else
    {
        current = *head;
        while (current->next != NULL && current->next->id < new->id)
        {
            current = current->next;
        }
        new->next = current->next;
        current->next = new;
    }
}

void cw_vm_insert_sort(t_champ **head)
{
	t_champ *sorted;
    t_champ *current;
    t_champ *next;

	sorted = NULL;
	current = *head;
    while (current != NULL)
    {
		next = current->next;
        cw_vm_insert(&sorted, current);
        current = next;
    }
    *head = sorted;
}
