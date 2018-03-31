.name		"brouette"
.comment	"Les fleurs sont nos amies!"

coquelicot:
	st		r1, r15
	st		r15, 26
	st		r15, 304
	st		r15, 310
	ld		%0, r16
	fork	%:paquerette

fougere:
	live	%2764347
	st		r2, -9
	st		r2, -18
	st		r2, -27
	st		r2, -36
	st		r2, -45
	st		r2, -54
	st		r2, -63
	st		r2, -72
	st		r2, -81
	st		r2, -90
	st		r2, -99
	st		r2, -108
	st		r2, -117
	st		r2, -126
	st		r2, -135
	st		r2, -144
	st		r2, -153
	st		r2, -162
	st		r2, -171
	st		r2, -180
	st		r2, -189
	st		r2, -198
	st		r2, -207
	st		r2, -216
	st		r2, -225
	st		r2, -234
	st		r2, -243
	st		r2, -252
	st		r2, -261
	st		r2, -270
	st		r2, -279
	st		r2, -288
	st		r2, -297
	st		r2, -306
	st		r2, -315
	st		r2, -324
	st		r2, -333
	st		r2, -342
	st		r2, -351
	st		r2, -360
	st		r2, -369
	st		r2, -378
	st		r2, -387
	st		r2, -396
	st		r2, -405
	st		r2, -414
	st		r2, -423
	st		r2, -432
	st		r2, -441
	st		r2, -450
	st		r2, -459
	st		r2, -468
	st		r2, -477
	st		r2, -486
	st		r2, -495
	zjmp	%:fougere

paquerette:					#PROC 2
	live	%21763847
	fork	%:mimosa		#CREATE PROC 3
	fork	%:tulipe		#CREATE PROC 4
	live	%21443847
	ld		%393727, r7		#00 06 01 ff
	ld		%12, r8
	ld		%11, r9
	ld		%0, r16
	zjmp	%:lily

mimosa:						#PROC 3
	live	%21763847
	fork	%:hibiscus		#CREATE PROC 5
	ld		%151220239, r7	#09 03 70 0f
	ld		%10, r8
	ld		%9, r9
	ld		%0, r16
	zjmp	%:lily

tulipe:						#PROC 4
	ld		%0, r7
	ld		%0, r8
	ld		%0, r9
	ld		%0, r16
	zjmp	%:fougere

hibiscus:					#PROC 5
	ld		%190056200, r7	#0b 54 07 08
	ld		%8, r8
	ld		%7, r9
	live	%214763847
	ld		%0, r16
	add		r16, r16, r16

lily:
	sti		r7, r8, r9
