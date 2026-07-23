/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _CTRDL_LOADER_H
#define _CTRDL_LOADER_H

#include "Handle.h"
#include "Stream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

CTRDLHandle* ctrdl_loadObject(const char* name, int flags, CTRDLStream* stream, CTRDLResolverFn resolver, void* resolverUserData);
bool ctrdl_unloadObject(CTRDLHandle* handle);

#if defined(__cplusplus)
}
#endif // cplusplus

#endif /* _CTRDL_LOADER_H */