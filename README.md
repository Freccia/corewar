# Corewar
"Core War (or Core Wars) is a Programming game in which two or more battle programs (called warriors) compete for the control of the MARS virtual computer (Memory Array Redcode Simulator). These battle programs are written in an abstract Assembly language called Redcode. The object of the game is to cause all processes of the opposing program(s) to terminate, leaving your program in sole possession of the machine." (from: Wikipedia)

This project is made of two parts, an *assembler* and a *virtual machine*.
The assembler compiles the _redcode_ in a ``.cor`` file, which can be run with the virtual machine.

You can find already builded programs in `test/ressources/ctrl_cor`, and redcode examples in `test/ressources/test_asm`.

## Build
Release build:
```
$ make
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

Running a match:
```
$ ./corewar -g brouette.cor test/ressources/test_asm/bee_gees.cor test/ressources/ctrl_cor/helltrain.cor
```


![Alt text](https://media.giphy.com/media/oHxsaLVY5COfNPuMRc/giphy.gif "Corewar")

