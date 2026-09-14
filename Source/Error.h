/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _CTRDL_ERROR_H
#define _CTRDL_ERROR_H

#include <dlfcn.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void ctrdl_setLastError(const char* fmt, ...) __attribute__(( format(printf, 1, 2) ));
const char* ctrdl_getLastError(void);
void ctrdl_clearLastError(void);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif /* _CTRDL_ERROR_H */