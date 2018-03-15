/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_asm_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:38:59 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/15 13:09:14 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "super_test_3000.h"
#include "asm_lexer.h"

void test_asm_lexer()
{
    lex("data/test_asm/Gagnant.s");
    lex("data/test_asm/zork.s");
    lex("data/test_asm/42.s");
    MU_ASSERT(42 > 0, "you're doing it wrong");
}
