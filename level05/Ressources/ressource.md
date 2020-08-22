# Format String Exploit



https://axcheron.github.io/exploit-101-format-strings/

https://www.codemopolitan.com/format-strings/

```bash
level05@OverRide:~$ ./level05
QWERTY
qwerty
a `fgets()` call is store the input in a buffer of 100 chars. A loop on the buffer for transform the input into lowercase.
