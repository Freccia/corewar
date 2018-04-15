# Corewar
"Core War (or Core Wars) is a Programming game in which two or more battle programs (called warriors) compete for the control of the MARS virtual computer (Memory Array Redcode Simulator). These battle programs are written in an abstract Assembly language called Redcode. The object of the game is to cause all processes of the opposing program(s) to terminate, leaving your program in sole possession of the machine." (from: Wikipedia)

This project is made of two parts, an *assembler* and a *virtual machine*.
The assembler compiles the _redcode_ in a ``.cor`` file, which can be run with the virtual machine.

You can find already builded programs in `test/ressources/ctrl_cor`, and redcode examples in `test/ressources/test_asm`.


## The implementation
This Corewar implementation follows the directives of 42's school Corewars. This means the project is a little different from a classical Corewar. For example the champions are not charged randomly in the memory, there are more instructions and some registers are availables for the processes.
You can find the 42's project directives pdf in: `test/ressources/ress_42/pdf/corewar.pdf`

### GUI
The GUI allows easy debugging with a step by step mode and showing the processes registers on the bottom right box.
You can use ' _space_ ' to launch/pause the VM, ' _s_ ' to make a step, up/down arrows to adjust 'Cycles by Step', and ' _o/p_ ' to iterate through the processes registers.
The left/right arrows adjusts the speed of the execution.

## The code
We tryied to keep the code simple and easy to modify.

In the VM for example all instructions use the function ``int32_t vm_readarg()`` to get the arguments, so adding an instruction should be easy.
Mooving a pointer in the VM is done with ``uint8_t *vm_move()`` which allows the memory to be circular (overflows ends on the memory low addresses).
All writings are done with ``void vm_write()`` which writes in the memory and notifies the gui at the same time.

The instructions structure is in `src/vm/op.c` and the header is in 'includes/op.h'.

## Build
Release build:
```
$ make
```
Sanitize build (flags: `-fsanitize=address,undefined -ferror-limit=5`):
```
$ make san
```
Developer build (flags: `-g3 -DDEBUG`):
```
$ make dev
```

## Examples
This is an example of a simple corewar program written in simil-asm (redcode):
```
$ cat test/ressources/test_asm/bee_gees.s
.name "stayin' alive"
.comment "Ha, Ha, Ha, stayiiiiin' aliiiiiiiiiive"
	
sti		r1, %:live, %1		;change lives with the right value
sti		r1, %:live2, %1		;
ld		%1, r3
ld		%33, r6

#While (r2 < 10)
forks:
add		r2, r3, r2		;increment r2
xor		r2, %15, r4		;if (r4) {carry = 0}

live2:
live	%4
zjmp	%:endwhile		;if (carry)
fork	%:forks
ld		%0, r4			;carry = 1
zjmp	%:forks

#EndWhile
endwhile:
ld		%0, r4			;carry = 1

live:
live	%4
zjmp	%:live
```

Compile a corewar program:
```
$ ./asm  test/ressources/test_asm/bee_gees.s
Writing output program to test/ressources/test_asm/bee_gees.cor
```

Run a match:
```
$ ./corewar -g brouette.cor test/ressources/test_asm/bee_gees.cor test/ressources/ctrl_cor/helltrain.cor
```

![Alt text](https://media.giphy.com/media/oHxsaLVY5COfNPuMRc/giphy.gif "Corewar")


### Usage
```
./corewar: -: illegal option
corewar: Usage: ./corewar [ options ] <[-n <champ.id>] champ.cor> <...>
	-g      : Ncurses GUI
		- space      : pause/resume execution
		- o/p        : navigate through processes (show registers)
		- s          : step by step
		- up/down    : cycles by step
		- left/right : cycles/second
	-d N    : Dumps memory after N execution cycles
	-c N    : CTMO - Cycles till memory opens
	-p N    : Pause a `N` cycle in GUI
	-v N    : Sets verbosity level to N (bitwise)
		- 0 : Show essentials
		- 1 : Show lives
		- 2 : Show cycles
		- 4 : Show operations
		- 8 : Show deaths
		-16 : Show PC movement
```

