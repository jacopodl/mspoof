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
 
    

# GPLv3 License
    Copyright (C) 2017

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
