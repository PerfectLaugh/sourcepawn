// vim: set ts=8 sts=2 sw=2 tw=99 et:
//
//  Copyright (c) ITB CompuPhase, 1997-2006
//
//  This software is provided "as-is", without any express or implied warranty.
//  In no event will the authors be held liable for any damages arising from
//  the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1.  The origin of this software must not be misrepresented; you must not
//      claim that you wrote the original software. If you use this software in
//      a product, an acknowledgment in the product documentation would be
//      appreciated but is not required.
//  2.  Altered source versions must be plainly marked as such, and must not be
//      misrepresented as being the original software.
//  3.  This notice may not be removed or altered from any source distribution.

#pragma once

#include <stddef.h>

#include "errors.h"
#include "sc.h"
#include "scvars.h"

template <typename T>
static void
StringToCells(const char* str, size_t len, const T& litadd)
{
    ucell val = 0;
    int byte = 0;
    for (size_t i = 0; i < len; i++) {
        val |= (unsigned char)str[i] << (8 * byte);
        if (byte == sizeof(ucell) - 1) {
            litadd(val);
            val = 0;
            byte = 0;
        } else {
            byte++;
        }
    }
    if (byte != 0) {
        // There are zeroes to terminate |val|.
        litadd(val);
    } else {
        // Add a full cell of zeroes.
        litadd(0);
    }
}

// Returns true if compilation is in its second phase (writing phase) and has
// so far proceeded without error.
static inline bool
cc_ok()
{
    return sc_status == statWRITE && sc_total_errors == 0;
}