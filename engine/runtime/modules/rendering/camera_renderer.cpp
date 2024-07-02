/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#include "camera_renderer.h"

modules::camera_renderer::camera_renderer() = default;

void modules::camera_renderer::Render(const rendering::render_context context, const Camera &camera)
{
    context_ = context;
    camera_  = camera;
    /*
            PrepareBuffer();
            PrepareForSceneWindow();
            Cull();
            Setup();
            DrawVisibleGeometry();
            DrawUnsupportedShaders();
            DrawGizmos();
            Submit();*/
}

void modules::camera_renderer::Setup()
{
    //hand the camera's projection matrix to the context
    context_.SetupCameraProperties(camera_);
    /*
     auto flags = camera_.clear_flag;
    buffer_.ClearRenderTarget
        (
            flags <= CameraClearFlags.Depth,
            flags == CameraClearFlags.Color,
            flags == CameraClearFlags.Color ? _camera.backgroundColor.linear : Color.clear
            );
     */
    context_.ExecuteCommandBuffer(buffer_);
    buffer_.clean();
}
