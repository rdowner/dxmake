/*
 * Copyright (c) 2003-2011,2023 The DragonFly Project.  All rights reserved.
 *
 * This code is derived from software contributed to The DragonFly Project
 * by Matthew Dillon <dillon@backplane.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of The DragonFly Project nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include "defs.h"

#ifdef sgi
#define vfork   fork
#endif

typedef struct CommandLineInterface CLI;
typedef struct Process              Process;

Prototype long Execute_Command(char *, short);
Prototype void InitCommand(void);
Prototype long LoadSegLock(long, char *);

char RootPath[512];

extern struct Library *SysBase;

void
InitCommand(void)
{
    getcwd(RootPath, sizeof(RootPath));
}

/*
 *  cmd[-1] is valid space and, in fact, must be long word aligned!
 */

long
Execute_Command(char *cmd, short ignore)
{
    register char *ptr;

    for (ptr = cmd; *ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '\n'; ++ptr)
        ;


    /*
     *  Internal MakeDir because AmigaDOS 2.04's MakeDir is unreliable
     *  with RunCommand() (it can crash)
     *
     *  Internal CD because we special case it
     */

    if (ptr - cmd == 2 && strncasecmp(cmd, "cd", 2) == 0) {
        short err = 0;

        while (*ptr == ' ' || *ptr == '\t')
            ++ptr;
        {
            short len = strlen(ptr);    /*  XXX HACK HACK */
            if (len && ptr[len-1] == '\n')
                ptr[len-1] = 0;
        }
        if (*ptr == 0)
            err = chdir(RootPath);
        else
            err = chdir(ptr);
        if (err != 0) {
            err = 20;
            printf("Unable to cd %s\n", ptr);
        }
        return((ignore) ? 0 : err);
    }

    /*
     * run command cmd
     *
     */

    {
        int err;

        if ((err = vfork()) == 0) {
            execlp("/bin/sh", "/bin/sh", "-c", cmd, NULL);
            exit(30);
        } else {
            int uwait;

            while (wait(&uwait) != err || WIFEXITED(uwait) == 0)
                ;
            err = WEXITSTATUS(uwait);
        }
        if (err)
            printf("Exit code %d %s\n", err, (ignore) ? "(Ignored)":"");
        if (ignore)
            return(0);
        return(err);
    }
}

