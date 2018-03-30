.name "zork"
.comment "I'M ALIIIIVE"

test:	ldi	%:trash, %1, r1

trash:	live	%42

lol:	sti		r1, %:trash, %1
		and		%0, %0, r5
