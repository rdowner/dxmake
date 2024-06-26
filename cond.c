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

Prototype int pushIf(IfNode **ifBase, int value);
Prototype int popIf(IfNode **ifBase);
Prototype int elseIf(IfNode **ifBase);

int
pushIf(IfNode **ifBase, int value)
{
    IfNode *ifn = malloc(sizeof(IfNode));

    bzero(ifn, sizeof(IfNode));
    ifn->if_Next = *ifBase;
    *ifBase = ifn;

    if (ifn->if_Next == NULL || ifn->if_Next->if_Value)
        ifn->if_Value = value;
    else
        ifn->if_Value = 0;
    return(ifn->if_Value);
}

int
popIf(IfNode **ifBase)
{
    IfNode *ifn = *ifBase;

    *ifBase = ifn->if_Next;
    free(ifn);
    if ((ifn = *ifBase) == NULL)
        return(1);
    else
        return(ifn->if_Value);
}

int
elseIf(IfNode **ifBase)
{
    IfNode *ifn = *ifBase;

    if (ifn->if_Next == NULL || ifn->if_Next->if_Value) {
        ifn->if_Value = !ifn->if_Value;
    } else {
        assert(ifn->if_Value == 0);
    }
    return(ifn->if_Value);
}


