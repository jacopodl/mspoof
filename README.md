![](https://img.shields.io/badge/Language-C-orange.svg)
![](https://img.shields.io/badge/version-1.0.1-green.svg)
![GPLv3 License](https://img.shields.io/badge/License-GPLv3-blue.svg)
![](https://img.shields.io/badge/Supported%20Os-Linux%2FBSD%2FMac%20Os-red.svg)

# mspoof
Simple utility for Linux/Mac Os that can change mac address of network interface.

# Getting and compiling the code
:warning: mspoof require cmake to automate build process, please install cmake first!

    $ git clone https://github.com/jacopodl/mspoof
    $ cd mspoof
    $ cmake . && make
# Usage
    mspoof interface mac|[OPTION]
## Example
Some short usage example:

Scenario:

- interface name: enp33s0
- interface mac: a0:cc:ee:f0:ac:d0

Change mac to aa:bb:cc:aa:bb:cc:

    mspoof enp33s0 aa:bb:cc:aa:bb:cc
If would you like restart interface after change add --restart flags

    mspoof enp33s0 aa:bb:cc:aa:bb:cc --restart
____
Change mac to random address:

    mspoof enp33s0 -r
    -or-
    mspoof enp33s0 --random
____
Restore mac address (work only on Linux :disappointed:):

    mspoof enp33s0 --reset
____
Show interface list:

    mspoof -l

If your system is Linux you can see which interface have spoofed mac, unfortunately :disappointed: (for now i hope) this features working only on Linux os :cry:
