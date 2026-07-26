/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _CTRDL_STREAM_H
#define _CTRDL_STREAM_H

#include <dlfcn.h>
#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void ctrdl_makeFileStream(CTRDLStream* stream, FILE* f);
void ctrdl_makeMemStream(CTRDLStream* stream, const void* buffer, size_t size);

#if defined(__cplusplus)
}
#endif // cplusplus

#endif /* _CTRDL_STREAM_H */