/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef CAMERA_RENDERER_H
#define CAMERA_RENDERER_H

#include "../../core/rendering/render_context.h"
#include "../Camera.h"

namespace modules
{
    class camera_renderer
    {
    public:
        void Render()
        {

        };
        void Render(rendering::render_context context, Camera value)
        {

        };

    private:
        Camera                    _camera;
        rendering::render_context _context;

    };
} // namespace modules

#endif //CAMERA_RENDERER_H
