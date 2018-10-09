# RS-AES-OAEP
Implementation of RS-AES-OAEP in C++ with LargeInteger numbers class


do the following:
cd RSAES_OAEP
cd source
g++ -std=c++14 -I../header *.cpp -o RSAES_OAEP.exe
./RSAES_OAEP.exe


The starting point was to implement a class which allows to calculate using large integers. 
We did not yet do operator overload. But in this initial version the following functions are implemented 
for integegers with 'infinite' size: 

- add
- sub
- multiply
- equals
- less than
- shift
- divide
- remainder (mod)
- modularExponentation
- modularExponentiation a faster algorithm 

Then other / logic functions for large integers were added: 
- concatenation 
- Xor 
- flip 

Based on these functions the RSAES-OAEP algorithm could be implemented. 
The implemention here shows how these algorithms may work but there is not much emphasis 
on efficiency yet. These could be a good start for a hardware implementation. 

In EmeOaep class only encode and decode exist. This project does use keys but does not 
yet generate keys. 

Anyway the Integer calculation can be used stand alone. Other implementation embed the calculations 
into their code which makes it faster. But we wanted to have a LargeInteger solution. 

Have fun will add some more docs over time. 
Greetings 
 Andreas Falkenberg
 
