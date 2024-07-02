/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef CUSTOM_RENDER_PIPELINE_H
#define CUSTOM_RENDER_PIPELINE_H

#include "render_pipeline.h"
#include "camera_renderer.h"

namespace modules
{
    class custom_render_pipeline final : public rendering::render_pipeline
    {
    public:
        custom_render_pipeline();

    protected:
        void Render(rendering::render_context context, const std::list<Camera> &cameras) override;

    private:
          camera_renderer camera_renderer_;
    };

} // namespace modules
#endif //CUSTOM_RENDER_PIPELINE_H
