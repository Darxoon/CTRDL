/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _CTRDL_STREAM_H
#define _CTRDL_STREAM_H

#include <dlfcn.h>
#include <stdio.h>

void ctrdl_makeFileStream(CTRDLStream* stream, FILE* f);
void ctrdl_makeMemStream(CTRDLStream* stream, const void* buffer, size_t size);

#endif /* _CTRDL_STREAM_H */