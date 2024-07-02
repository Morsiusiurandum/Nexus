/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef BINDABLE_H
#define BINDABLE_H

#include "../Graphics.h"
using namespace directx11;

namespace directx11
{
    class Bindable
    {

    public:
        virtual void Bind(Graphics &graphics) = 0;
        virtual      ~Bindable() = default;

    protected:
        static auto GetDevice(Graphics &graphics) noexcept -> ID3D11Device *;
        static auto GetDeviceContext(Graphics &graphics) noexcept -> ID3D11DeviceContext *;
    };
}

#endif
