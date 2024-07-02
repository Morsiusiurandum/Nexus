/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef COMMAND_BUFFER_H
#define COMMAND_BUFFER_H

#include "Color.h"
#include "../core/rhi/graphics.h"
#include <string>
#include <vector>

namespace rendering
{
    class command_buffer
    {
    public:
        void clean();
        void clear_render_target(bool clearDepth, bool clearColor, Color backgroundColor, float depth);
        void BeginSample(std::string name);

    private:
        std::vector<int> command_;
    };
}

#endif //COMMAND_BUFFER_H
