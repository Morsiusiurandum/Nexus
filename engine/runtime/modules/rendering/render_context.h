/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include "command_buffer.h"
#include "../Camera.h"

namespace rendering
{

    class render_context
    {
    public:
        void SetupCameraProperties(Camera camera);
        void ExecuteCommandBuffer(command_buffer buffer);
    };

} // namespace rendering

#endif //RENDER_CONTEXT_H
