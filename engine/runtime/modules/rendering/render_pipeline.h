/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef RENDER_PIPELINE_H
#define RENDER_PIPELINE_H

#include "render_context.h"
#include <list>

class Camera;

namespace rendering
{
    class render_pipeline
    {
    public:
        virtual ~render_pipeline() = default;

    protected:
        virtual void Render(render_context context, const std::list<Camera> &cameras) =0;
    };

} // namespace rendering

#endif //RENDER_PIPELINE_H
