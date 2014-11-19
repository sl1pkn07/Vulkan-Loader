/**************************************************************************
 *
 * Copyright 2014 Lunarg, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/
#pragma once

extern "C" {
#include "glv_common.h"
#include "glv_trace_packet_identifiers.h"
}
#include "glvreplay_window.h"

namespace glv_replay {

enum GLV_REPLAY_RESULT
{
    GLV_REPLAY_SUCCESS = 0,
    GLV_REPLAY_ERROR,          // internal error unrelated to the specific packet
    GLV_REPLAY_INVALID_ID,     // packet_id invalid
    GLV_REPLAY_BAD_RETURN,     // replay return value != trace return value
    GLV_REPLAY_CALL_ERROR,     // replaying call caused an error
    GLV_REPLAY_INVALID_PARAMS, // trace file parameters are invalid
};

// entrypoints that must be exposed by each replayer library
extern "C"
{
typedef int (GLVTRACER_CDECL *funcptr_glvreplayer_initialize)(glv_replay::Display* pDisplay, unsigned int debugLevel);
typedef void (GLVTRACER_CDECL *funcptr_glvreplayer_deinitialize)();
typedef glv_replay::GLV_REPLAY_RESULT (GLVTRACER_CDECL *funcptr_glvreplayer_replay)(glv_trace_packet_header* pPacket);
}

struct glv_trace_packet_replay_library
{
    void* pLibrary;
    funcptr_glvreplayer_initialize Initialize;
    funcptr_glvreplayer_deinitialize Deinitialize;
    funcptr_glvreplayer_replay Replay;
};

class ReplayFactory {
public:
    glv_trace_packet_replay_library *Create(uint8_t tracerId);
    void Destroy(glv_trace_packet_replay_library** ppReplayer);
};
} // namespace glv_replay
