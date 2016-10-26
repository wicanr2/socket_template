# compile simple ipv6 client and server #
make

# clean ipv6 client and server #
make clean

# start server #
open terminal
./ipv6_server

# test concurrent client #
open terminal
./test6.sh

# assembly debug
- create assembler code:
c++ -S -fverbose-asm -g -O2 test.cc -o test.s
- create asm interlaced with source lines:
as -alhnd test.s > test.lst
