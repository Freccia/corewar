# Corewar
"Core War (or Core Wars) is a Programming game in which two or more battle programs (called warriors) compete for the control of the MARS virtual computer (Memory Array Redcode Simulator). These battle programs are written in an abstract Assembly language called Redcode. The object of the game is to cause all processes of the opposing program(s) to terminate, leaving your program in sole possession of the machine." (Wikipedia)

This project is made of two parts, an *assembler* and a *virtual machine*.
The assembler compiles the _redcode_ in a ``.cor`` file, which can be run with the virtual machine.

You can find already builded programs in `test/ressources/ctrl_cor`, and redcode examples in `test/ressources/test_asm`.

## Build
Release build:
```
$ make
```

## Examples
```
$ ./asm brouette.s
$ ./corewar -g brouette.cor test/ressources/ctrl_cor/helltrain.cor
```


![Alt text](http://g.recordit.co/IVM8xLYxWF.gif "Corewar")

