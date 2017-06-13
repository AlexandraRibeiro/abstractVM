push float(123456.10714589); float precision is truncating to 123456.1
dump; should show 123456.1, the real max precision float 
assert float(123456.107145897895456); shoud be true, even different from push
; 									but too precise for float
assert float(123456.10714589); shoud be true, but too precise for float
assert float(123456.1) ; shoud be true 'real value'
push int8(1)
mul; result should be 123456.1
dump; should show 123456.1 , the real max precision float
assert float(123456.10714589) ; shoud be true, but too precise for float
assert float(123456.1) ; shoud be true 'real value'
pop
exit