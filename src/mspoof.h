/*
    * mspoof
	* Copyright (C) 2017 - 2018 Jacopo De Luca
	*
	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, either version 3 of the License, or
	* (at your option) any later version.
	* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	* GNU General Public License for more details.
	* You should have received a copy of the GNU General Public License
	* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MSPOOF
#define MSPOOF

#include <stdbool.h>
#include <net/if.h>

#define APPNAME "mspoof"
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 1

typedef struct {
    bool shl;
    bool set;
    bool rset;
    bool rstart;
    bool mac;
    bool rmac;
    unsigned int filter;
    char iface_name[IFNAMSIZ];
    struct netaddr_mac iface_hwaddr;
} Options;

int set_iface_mac(Options *opt);

int show_iface(unsigned int filter);

void usage();

#endif // MSPOOF