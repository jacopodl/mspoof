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

#ifndef ARGSX_H
#define ARGSX_H

#define ARGSX_VERSION_MAJOR        @VERSION_MAJOR@
#define ARGSX_VERSION_MINOR        @VERSION_MINOR@
#define ARGSX_VERSION_PATCH        @VERSION_PATCH@

typedef struct ax_lopt {
    char *name;
    int args;
    char opt;
} ax_lopt;

typedef enum ax_einfo {
    no_err = -1,
    short_opt = 0,
    long_opt = 1
} ax_einfo;

extern char *ax_curr;       // Pointer to current position string
extern char *ax_arg;        // Pointer to arg
extern int ax_cursor;       // Current position
extern int ax_opterr;       // Show errors
extern ax_einfo ax_etype;   // Error type
extern short ax_loptidx;    // Long options index

/* Switch constant */
#define ARGSX_BAD_OPT   0xFF
#define ARGSX_FEW_ARGS  0xFE
#define ARGSX_NONOPT    0xFD
#define ARGSX_LOPT      0xFC

/* ax_lopt mode */
#define ARGSX_NOARG     0x00
#define ARGSX_REQ_ARG   0x01

#ifdef __cplusplus
extern "C" {
#endif

int argsx(int argc, char **argv, char *opt, struct ax_lopt *lopt, unsigned short lopt_size, char tr);

#ifdef __cplusplus
};
#endif

#endif  // ARGSX_H