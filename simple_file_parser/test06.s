; No operator priority, only parenthesis
;
; Input expression input:
; 9*3:7.-45*3=
; ==============
;
;Starting...
push int8(9)
push int8(3)
mul
push float(7.)
div
push float(45)
sub
push float(3)
mul
;show result
dump
;clear stack
pop
;Leaving...
exit
;;   ;bye!