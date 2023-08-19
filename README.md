# libmcprotocol
## About
libmcprotocol is meant to be a faster and more efficient alternative to PrismarineJS's mineflayer. It's written in C, and can easily be ported to pretty much any other programming language.
## To-do
* Change the makefile to compile libmcprotocol as a shared library
## Example
See `example.c` for a quick example that uses libmcprotocol to create a simple Minecraft client in C. To compile `example.c`, run the command:
```sh
gcc example.c -o example -L. -Iinclude -lmcprotocol
```
## License
libmcprotocol is licensed under LGPLv3.