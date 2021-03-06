/*
 * Copyright (c) 2016 Jacopo De Luca
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#ifndef SPARK_SPKSOCK_BPF_H
#define SPARK_SPKSOCK_BPF_H

#include <spksock.h>

#define SPKBPF_MAXPATHLEN   11
#define SPKBPF_MAXDEV       99

struct SpkBpf {
    int sock;
    unsigned char *buf;
    unsigned char *cursor;
    int caplen;
    int buflen;
};

static int spksock_bpf_read(struct SpkSock *, unsigned char *, struct SpkTimeStamp *);

static int spksock_bpf_setdir(struct SpkSock *, enum SpkDirection);

static int spksock_bpf_setnblock(struct SpkSock *, bool);

static int spksock_bpf_setprc(struct SpkSock *, enum SpkTimesPrc);

static int spksock_bpf_setpromisc(struct SpkSock *, bool);

static int spksock_bpf_write(struct SpkSock *, unsigned char *, unsigned int);

static int __bpf_get_hwaddr(struct SpkSock *ssock);

static void spksock_bpf_finalize(struct SpkSock *);

#endif
