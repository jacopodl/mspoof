/*
	* ArgsX, Simple C/C++ options parser.
	* Copyright (C) 2014-2017 Jacopo De Luca
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
#include <stdlib.h>
#include <string.h>

#include "argsx.h"

char *ax_curr;
char *ax_arg;
int ax_cursor = 1;
int ax_opterr = 1;
ax_einfo ax_etype = no_err;
short ax_loptidx;


int argsx(int argc, char **argv, char *opt, struct ax_lopt *lopt, unsigned short lopt_size, char tr) {
    static unsigned short cmpd_arg = 1;
    static unsigned short cmpd_opt = 0;
    char *subopt;
    int ret;
    size_t len;

    ax_curr = argv[ax_cursor];
    if (ax_cursor >= argc)
        return -1;

    if (*ax_curr == tr) {
        if (*++ax_curr == tr && lopt != NULL) {
            ax_curr++;
            for (short i = 0; i < (lopt_size / sizeof(struct ax_lopt)); i++) {
                if (strcmp(lopt[i].name, ax_curr) == 0) {
                    ret = (lopt[i].opt == 0) ? ARGSX_LOPT : lopt[i].opt;
                    ax_loptidx = i;
                    ax_cursor++;
                    if (lopt[i].args == ARGSX_NOARG)
                        return ret;
                    if (ax_cursor >= argc || *argv[ax_cursor] == tr) {
                        if (ax_opterr)
                            fprintf(stderr, "Argument --%s expected one argument\n", ax_curr);
                        ax_etype = long_opt;
                        return ARGSX_FEW_ARGS;
                    }
                    ax_arg = argv[ax_cursor++];
                    return ret;
                }
            }
            if (ax_opterr)
                fprintf(stderr, "Unrecognized argument: --%s\n", ax_curr);
            ax_etype = long_opt;
            return ARGSX_BAD_OPT;
        }
        ax_curr += cmpd_opt;
        ret = *ax_curr;
        if ((subopt = strchr(opt, *ax_curr)) != 0) {
            if (*++subopt == '!') {
                if (ax_cursor + cmpd_arg >= argc || *argv[ax_cursor + cmpd_arg] == tr) {
                    if (strlen(ax_curr + 1) > 0 && cmpd_arg == 1) {
                        ax_arg = ax_curr + 1;
                        ax_cursor++;
                        return ret;
                    }
                    if (ax_opterr)
                        fprintf(stderr, "Argument -%c expected one argument\n", *ax_curr);
                    ax_etype = short_opt;
                    return ARGSX_FEW_ARGS;
                }
                ax_arg = argv[ax_cursor + cmpd_arg++];
            }
            len = strlen(ax_curr);
            if (len > 1 && cmpd_opt <= len)
                cmpd_opt++;
            else {
                ax_cursor += cmpd_arg;
                cmpd_arg = 1;
                cmpd_opt = 0;
            }
            return ret;
        }
        if (ax_opterr)
            fprintf(stderr, "Unrecognized argument: -%c\n", *ax_curr);
        ax_etype = short_opt;
        return ARGSX_BAD_OPT;
    }
    ax_arg = argv[ax_cursor++];
    return ARGSX_NONOPT;
}