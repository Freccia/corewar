/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_asm_encoder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:38:59 by mcanal            #+#    #+#             */
/*   Updated: 2018/03/22 21:21:40 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "super_test_3000.h"

#include "corewar.h"

uint32_t reg_ctrl[REG_NUMBER] = {0};
uint32_t flag = 0;
uint8_t mem[MEM_SIZE] = {0};

static void check_memory(size_t mem_size_to_check, t_proc *proc)
{
	int i;

	//check registers
	for (i = 0; i < REG_NUMBER ; i++) {
		MU_ASSERT(
			proc->reg[i] == reg_ctrl[i],
			"register mismatch: test:%d, ctrl:%d",
			proc->reg[i], reg_ctrl[i]
		);
	}

	//check flag
	MU_ASSERT(
		proc->flags == flag,
		"flag mismatch: test:%d, ctrl:%d",
		proc->flags, flag
	);

	//check mem
	i = memcmp(mem, g_cw->mem, mem_size_to_check);
	if (i) {
		fprintf(stderr, "Test memory:\n");
		ft_print_memory(g_cw->mem, mem_size_to_check);
		fprintf(stderr, "Ctrl memory:\n");
		ft_print_memory(mem, mem_size_to_check);
	}
	MU_ASSERT(
		!i, "memory diff"
	);
}

void test_vm_add()
{
	t_proc	proc;
	t_cw	gcw;

	bzero(&gcw, sizeof(t_cw));
	g_cw = &gcw;
	bzero(&flag, sizeof(uint32_t));
	bzero(&reg_ctrl, sizeof(uint32_t) * REG_NUMBER);
	bzero(mem, MEM_SIZE);
	reg_ctrl[2] = 10;
	reg_ctrl[3] = 12;
	reg_ctrl[1] = 22;

	bzero(&proc, sizeof(proc));
	proc.reg[2] = 10;
	proc.reg[3] = 12;
	proc.pc = (unsigned char *)&gcw.mem;
	bzero(gcw.mem, sizeof(gcw.mem));
	gcw.mem[0] = 0x4;
	gcw.mem[1] = 0x54;
	gcw.mem[2] = 0x2;
	gcw.mem[3] = 0x3;
	gcw.mem[4] = 0x1;

	memcpy(mem, g_cw, 32);
	cw_add(&proc, gcw.mem);

	check_memory(32, &proc);
}

void test_vm()
{
	int r1;
	t_cw	cw;
	char *av[] = {"./supervm3000", "data/ctrl_cor/zork.cor", NULL};
	int ac = 2;
	int ret;

	ft_bzero(&cw, sizeof(t_cw));
	r1 = cw_vm_parse_opt(ac, av, &cw);

	/* ft_bzero(&cw, sizeof(t_cw)); */
	ret = cw_vm_init(ac, av, r1);
	MU_ASSERT_FATAL(
		ret == EXIT_SUCCESS,
		"cw vm init failed: ret:%d",
		ret
	);

	ret = cw_vm_run();
	MU_ASSERT_FATAL(
		cw_vm_run() == EXIT_SUCCESS,
		"cw vm run failed"
	);
}
