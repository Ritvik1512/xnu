/*
 * Copyright 2013, winocm. <winocm@icloud.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 *   Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 *   Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 *   If you are going to use this software in any form that does not involve
 *   releasing the source to this project or improving it, let me know beforehand.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * PE kprintf interface
 */

#include <mach/mach_types.h>
#include <pexpert/pexpert.h>
#include <pexpert/machine/protos.h>
#include <pexpert/machine/boot.h>
#include <machine/machine_routines.h>
#include <kern/debug.h>
#include <stdarg.h>

#include "semihost.h"

void (*PE_kputc)(char c);

/**
 * PE_init_kprintf
 *
 * Initialize kprintf (for semihosting right now.)
 */ 
void PE_init_kprintf(boolean_t vm_initialized)
{
	if (PE_state.initialized == FALSE)
		panic("Platform Expert not initialized");
    
    if (!vm_initialized) {
#warning Semihosting configuration enabled;
        PE_kputc = PE_semihost_write_char;
    }    
}

/**
 * kprintf
 *
 * Sort of like printf, but outputs wherever PE_kputc will send it to.
 */ 
void kprintf(const char *format, ...)
{
	va_list   listp;

    va_start(listp, format);
    _doprnt(format, &listp, PE_kputc, 16);
    va_end(listp);
}
