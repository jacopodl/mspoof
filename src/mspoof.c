/*
    * mspoof
	* Copyright (C) 2017 Jacopo De Luca
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <argsx.h>
#include <spark.h>
#include <stdlib.h>

#include "mspoof.h"

int main(int argc, char **argv) {
    int ret;
    Options opt = {false, false, false, false, false, false, 0, "\0"};
    ax_lopt lopt[] = {{(char *) "help",    ARGSX_NOARG, 'h'},
                      {(char *) "version", ARGSX_NOARG, 'v'},
                      {(char *) "list",    ARGSX_NOARG, 'l'},
                      {(char *) "random",  ARGSX_NOARG, 'r'},
                      {(char *) "reset",   ARGSX_NOARG, 1},
                      {(char *) "restart", ARGSX_NOARG, 2}};

    while ((ret = argsx(argc, argv, (char *) "hvlr", lopt, sizeof(lopt), '-')) != -1) {
        switch (ret) {
            case 1:
                opt.rset = true;
                break;
            case 2:
                opt.rstart = true;
                break;
            case 'h':
                usage();
                return 0;
            case 'v':
                printf("%s V: %d.%d.%d\n", APPNAME, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
                return 0;
            case 'l':
                opt.shl = true;
                break;
            case 'r':
                opt.rmac = true;
                break;
            case ARGSX_LOPT:
                break;
            case ARGSX_BAD_OPT:
                return -1;
            case ARGSX_FEW_ARGS:
                return -1;
            case ARGSX_NONOPT:
                if (!opt.set) {
                    if (strlen(ax_arg) >= IFNAMSIZ) {
                        fprintf(stderr, "%s name too long.\n", ax_arg);
                        return -1;
                    }
                    strcpy(opt.iface_name, ax_arg);
                    opt.set = true;
                } else {
                    if (!eth_parse_addr(ax_arg, &opt.iface_hwaddr, false)) {
                        fprintf(stderr, "Malformed MAC address.\n");
                        return -1;
                    }
                    opt.mac = true;
                }
                break;
            default:
                break;
        }
    }

    if (opt.shl)
        return show_iface(opt.filter);

    if (opt.set && (!opt.mac && !opt.rmac && !opt.rset)) {
        fprintf(stderr, "Usage: %s interface_name [new_mac|[OPTION]].\n", APPNAME);
        return -1;
    }

    if (opt.set)
        return set_iface_mac(&opt);

    usage();
    return 0;
}

int set_iface_mac(Options *opt) {
    short flags;
    netaddr_mac(burned);

    if (getuid()) {
        fprintf(stderr, "Required elevated privileges!\n");
        return -1;
    }

    if (opt->rmac)
        eth_rndaddr(&opt->iface_hwaddr);
    else if (opt->rset) {
        if (netdev_burnedin_mac(opt->iface_name, &burned) != SPKERR_SUCCESS) {
            perror("netdev_burnedin_mac");
            return -1;
        }
        memcpy(&opt->iface_hwaddr, &burned, sizeof(struct netaddr_mac));
    }

    if (netdev_set_mac(opt->iface_name, &opt->iface_hwaddr) != SPKERR_SUCCESS) {
        fprintf(stderr, "Unable to set MAC address!\n");
        perror("netdev_set_mac");
        return -1;
    }

    if (opt->rstart) {
        if (netdev_get_flags(opt->iface_name, &flags) != SPKERR_SUCCESS) {
            fprintf(stderr, "Unable to get interface flags!\n");
            perror("netdev_get_flags");
            return -1;
        }
        flags &= ~IFF_UP;
        if (netdev_set_flags(opt->iface_name, flags) != SPKERR_SUCCESS) {
            fprintf(stderr, "Unable to set interface flags!\n");
            perror("netdev_set_flags");
            return -1;
        }
        sleep(2);
        flags |= IFF_UP;
        if (netdev_set_flags(opt->iface_name, flags) != SPKERR_SUCCESS) {
            fprintf(stderr, "Unable to set interface flags!\n");
            perror("netdev_set_flags");
            return -1;
        }
    }
    return 0;
}

int show_iface(unsigned int filter) {
    struct NetDevice *netdev;
    netaddr_mac(mac);
    netaddr_mac(burned);
    int err;
    char *strmac = NULL;
    char *strbmac = NULL;

    if ((netdev = netdev_get_iflist(filter)) == NULL) {
        perror("netdev_get_iflist");
        return -1;
    }

    for (struct NetDevice *cursor = netdev; cursor != NULL; cursor = cursor->next) {
        err = netdev_burnedin_mac(cursor->name, &burned);
        strmac = eth_getstr(&cursor->mac, false);
        switch (err) {
            case SPKERR_SUCCESS:
                strbmac = eth_getstr(&burned, false);
                printf("%s\t\t%s - burned-in: %s\t%s\n", cursor->name, strmac, strbmac,
                       (strcmp(strmac, strbmac) == 0 ? (char *) "" : (char *) "[spoofed]"));
                free(strbmac);
                break;
            case SPKERR_ERROR:
                printf("%s\t\t%s - burnin: %s\n", cursor->name, strmac, (char *) "Err");
            default:
                printf("%s:\t\t%s\n", cursor->name, strmac);
                break;
        }
        free(strmac);
    }
    netdev_iflist_cleanup(netdev);
    return 0;
}

void usage() {
    printf("\n%s V: %d.%d.%d\n"
                   "Change MAC address of interface.\n", APPNAME, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    printf("Usage: %s interface_name [new_mac|[OPTION]] [OPTIONS...]\n\n"
                   "\t-h, --help   \tPrint this help and exit.\n"
                   "\t-v, --version\tPrint version and exit.\n"
                   "\t-l, --list   \tPrint all network interface with name and MAC.\n"
                   "\t-r, --random \tBuild and set random MAC.\n"
                   "\t--reset      \tRestore burned-in MAC(if supported).\n"
                   "\t--restart    \tRestart interface after change.\n", APPNAME);
}