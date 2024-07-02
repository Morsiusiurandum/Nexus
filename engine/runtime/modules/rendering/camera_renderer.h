/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef CAMERA_RENDERER_H
#define CAMERA_RENDERER_H

#include "command_buffer.h"
#include "render_context.h"
#include "../Camera.h"

namespace modules
{
    class camera_renderer
    {
    public:
        camera_renderer();
        void Render(rendering::render_context context, const Camera &camera);;

    private:
        void Setup();
        /*void PrepareBuffer();
        void PrepareForSceneWindow();
        void Cull();

        void DrawVisibleGeometry();
        void DrawUnsupportedShaders();
        void DrawGizmos();
        void Submit();*/

    private:
        Camera                    camera_;
        rendering::command_buffer buffer_;
        rendering::render_context context_;

    };
} // namespace modules

#endif //CAMERA_RENDERER_H
