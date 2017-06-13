push int8(1)
push float(3)
div; result should be .3333333
dump; should show .3333333 , the real max precision float
assert float(.3333333333333333) ; shoud be true, but too precise for float
assert float(.333333333338) ; shoud be true, even its false in reality
;							 but the precision of float cannot see the difference
assert float(.3333333) ; shoud be true 'real value'
pop
exit