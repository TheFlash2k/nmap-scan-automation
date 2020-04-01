# nmap-scan-automation

I was bored during this quarantine so I decided to challenge myself in making a script. I didn't know of what, so I made
an nmap scan automation with -sC -sV -oA parameters pre-defined. And because I use these parameters only, so, yeah, it did
make it easier for me to enumerate the machines i was scanning by just typing the ip and nothing else.


[^] Usage
[*] ./nmapScan -i
[*] ./nmapScan -f
[*] ./nmapScan -h

[>] -i | --ip - This tag is used to define the ip address.
[*] You don't have to define an ip address with the tag. The program will ask you for it.

[>] -f | --folder - This tag is used to define the name of the folder in which the files from the scan will be saved.
[*] If you use only -f tag, the program will automatically prompt you for ip input.

[>] -h | --help - This tag displays the help menu i.e. this menu.


Requirements:
[>]  Termcolor.hpp:
In order to compile it, you're going to need Termcolor.hpp which is written by @ikalnytskyi. It can cloned from this link:
https://github.com/ikalnytskyi/termcolor/blob/master/include/termcolor/termcolor.hpp

[>] Linux:
This script only works on linux.
