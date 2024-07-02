/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#include "command_buffer.h"

void rendering::command_buffer::clean()
{
    command_.clear();
}
void rendering::command_buffer::clear_render_target(bool clearDepth, bool clearColor, Color backgroundColor, float depth)
{
    if (clearDepth)
    {
        core::graphics::clear_depth(depth);
    }
    if (clearColor)
    {
        core::graphics::clear_color(0, 0, 0);
    }

}
