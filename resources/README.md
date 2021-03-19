# Eval Form
https://github.com/k-off/ft_ssl_md5/wiki/Evaluation-Sheet

# Notes

## MD5

Output 128 bit digest

512 bits chunks
append padding bits (multiple of 512 bits - 64 bits)
append 64 bit representation
-> after that the plain text length is multiples of 512bits

initialize 4 md5 buffers (32 bit sized)
4 different rounds (128 bits of 512 bit message per round)
after the 4th round, the result is added (%2^32) to initial buffer

each round is processed in 16 steps
each round consists of a function and 16 constants

after first block is proccessed the result is used to initialize buffers for 2nd block

Function F(B, C, D) = (B & C) | (~B & D)

Function G(B, C, D) = (B & D) | (C & ~D)

Function H(B, C, D) = B ^ C ^ D

Function I(B, C, D) = C ^ (B | ~D)

every step then behaves as follow

+% - Addition modulo 2^32
<<< - circular left shift
i - round * 16 + s
s - step
g - one of functions
X[k] - M[q * 16 * k] = the kth 32-bit word in the qth 512bit block of the message

A <- B +% (( A +% g(B, C, D) +% X[k] +% T[i]) <<< s)

process each 512 block

### Links
https://paginas.fe.up.pt/~ei10109/ca/md5.html
