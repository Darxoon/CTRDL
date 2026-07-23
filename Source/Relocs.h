/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _CTRDL_RELOCS_H
#define _CTRDL_RELOCS_H

#include "ELFUtil.h"
#include "Handle.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

bool ctrdl_handleRelocs(CTRDLHandle* handle, CTRDLElf* elf, CTRDLResolverFn resolver, void* resolverUserData);

#if defined(__cplusplus)
}
#endif // cplusplus

#endif /* _CTRDL_RELOCS_H */