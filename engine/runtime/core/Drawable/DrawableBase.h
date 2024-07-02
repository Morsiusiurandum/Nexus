/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef DRAWABLE_BASE_H
#define DRAWABLE_BASE_H

#include "../../platform/windows/directx11/Graphics.h"
#include <DirectXMath.h>
#include <vector>
using namespace directx11;
class DrawableBase
{
    template<class T>
    friend class MeshRenderer;

public:
    DrawableBase()                     = default;
    DrawableBase(const DrawableBase &) = delete;

    virtual ~DrawableBase()                                                         = default;
    virtual auto               Update(float dt) noexcept -> void                    = 0;
    [[nodiscard]] virtual auto GetTransformXM() const noexcept -> DirectX::XMMATRIX = 0;

    auto Draw(Graphics &graphics) const noexcept(!IS_DEBUG) -> void;
    auto AddBind(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG) -> void;
    auto AddIndexBuffer(std::unique_ptr<class IndexBuffer> index_buffer_uptr) noexcept -> void;

private:
    [[nodiscard]] virtual auto GetStaticBinds() const noexcept -> const std::vector<std::unique_ptr<Bindable>> & = 0;

private:
    const IndexBuffer                     *index_buffer_ptr = nullptr;
    std::vector<std::unique_ptr<Bindable>> bind_vector;
};

#endif //DRAWABLE_BASE_H
