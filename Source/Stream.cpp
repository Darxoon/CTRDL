/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <CTRPluginFramework.hpp>

#include "Stream.h"
#include "dlfcn.h"
#include "CTRPFFile.hpp" // IWYU pragma: keep

#include <format>
#include <string.h>

static bool ctrdl_fileSeekImpl(void* stream, size_t offset) {
    using namespace CTRPluginFramework;
    
    CTRPFFile* file = (CTRPFFile*)((CTRDLStream*)stream)->handle;
    int result = file->inner.Seek(offset, File::SET);
    if (R_FAILED(result)) {
        OSD::Notify(std::format("Seek failed: {} {}", R_SUMMARY(result), R_DESCRIPTION(result)));
    } else if (result) {
        OSD::Notify(std::format("Seek failed: {}", result));
    }
    return !result;
}

static bool ctrdl_fileReadImpl(void* s, void* out, size_t size) {
    using namespace CTRPluginFramework;
    
    CTRDLStream* stream = (CTRDLStream*)s;
    CTRPFFile* f = (CTRPFFile*)stream->handle;
    size_t dataRead = 0;

    while (dataRead < size) {
        const size_t toRead = size - dataRead;
        
        u32 bytesRead;
        int result = f->inner.Read((u8*)out + dataRead, toRead, bytesRead);
        if (R_FAILED(result)) {
            OSD::Notify(std::format("Read failed: {} {}", R_SUMMARY(result), R_DESCRIPTION(result)));
            return false;
        } else if (result) {
            OSD::Notify(std::format("Read failed: {}", result));
            return false;
        }

        dataRead += bytesRead;
    }

    return true;
}

static bool ctrdl_memSeekImpl(void* s, size_t offset) {
    using namespace CTRPluginFramework;
    
    CTRDLStream* stream = (CTRDLStream*)s;
    if (offset <= stream->size) {
        stream->offset = offset;
        return true;
    }

    OSD::Notify(std::format("Seek failed: {:#x} greater than {:#x}", offset, stream->size));
    return false;
}

static bool ctrdl_memReadImpl(void* s, void* out, size_t size) {
    using namespace CTRPluginFramework;
    
    CTRDLStream* stream = (CTRDLStream*)s;
    if (size <= (stream->size - stream->offset)) {
        memcpy(out, (u8*)stream->handle + stream->offset, size);
        stream->offset += size;
        return true;
    }

    OSD::Notify(std::format("Read failed: {:#x} at {:#x} out of bounds ({:#x})", size, stream->offset, stream->size));
    return false;
}

void ctrdl_makeFileStream(CTRDLStream* stream, CTRPFFile* f) {
    stream->handle = (void*)f;
    stream->seek = ctrdl_fileSeekImpl;
    stream->read = ctrdl_fileReadImpl;
}

void ctrdl_makeMemStream(CTRDLStream* stream, const void* buffer, size_t size) {
    stream->handle = (void*)buffer;
    stream->seek = ctrdl_memSeekImpl;
    stream->read = ctrdl_memReadImpl;
    stream->size = size;
    stream->offset = 0;
}