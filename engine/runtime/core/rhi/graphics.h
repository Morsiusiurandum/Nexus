/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef CORE_GRAPHICS_H
#define CORE_GRAPHICS_H

namespace core
{
    class graphics
    {
    public:
        void static clear_depth(float depth) noexcept;

        void static clear_color(float r, float g, float b);

    private:
        //  std::unique_ptr<directx11::Graphics> graphics_ptr;

    };

} // namespace core

#endif //CORE_GRAPHICS_H
