#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

#include "Bindable.h"

template<typename C>
class ConstantBuffer : public Bindable
{
public:
    ConstantBuffer(Graphics &graphics, const C &consts)
    {
        D3D11_BUFFER_DESC buffer_desc   = {};
        buffer_desc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
        buffer_desc.Usage               = D3D11_USAGE_DYNAMIC;
        buffer_desc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
        buffer_desc.MiscFlags           = 0U;
        buffer_desc.ByteWidth           = sizeof(consts);
        buffer_desc.StructureByteStride = 0U;

        D3D11_SUBRESOURCE_DATA subresource_data = {};
        subresource_data.pSysMem                = &consts;

        GRAPHICS_EXCEPTION(GetDevice(graphics)->CreateBuffer(&buffer_desc, &subresource_data, &const_buffer_com_ptr));
    }
/*
    ConstantBuffer(Graphics &gfx, const C &consts, UINT slot = 0u)
        : slot(slot)
    {
        D3D11_BUFFER_DESC cbd;
        cbd.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
        cbd.Usage               = D3D11_USAGE_DYNAMIC;
        cbd.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
        cbd.MiscFlags           = 0u;
        cbd.ByteWidth           = sizeof(consts);
        cbd.StructureByteStride = 0u;

        D3D11_SUBRESOURCE_DATA csd = {};
        csd.pSysMem                = &consts;
        
        GRAPHICS_EXCEPTION(GetDevice(gfx)->CreateBuffer(&cbd, &csd, &const_buffer_com_ptr));
    }
*/
    explicit ConstantBuffer(Graphics &graphics)
    {
        D3D11_BUFFER_DESC buffer_desc   = {};
        buffer_desc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
        buffer_desc.Usage               = D3D11_USAGE_DYNAMIC;
        buffer_desc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
        buffer_desc.MiscFlags           = 0U;
        buffer_desc.ByteWidth           = sizeof(C);
        buffer_desc.StructureByteStride = 0U;

        GRAPHICS_EXCEPTION(GetDevice(graphics)->CreateBuffer(&buffer_desc, nullptr, &const_buffer_com_ptr));
    }

    void Update(Graphics &graphics, const C &consts)
    {
        D3D11_MAPPED_SUBRESOURCE mapped_subresource;
        GRAPHICS_EXCEPTION(GetDeviceContext(graphics)->Map(const_buffer_com_ptr.Get(), 0U, D3D11_MAP_WRITE_DISCARD, 0U, &mapped_subresource));
        memcpy(mapped_subresource.pData, &consts, sizeof(consts));
        GetDeviceContext(graphics)->Unmap(const_buffer_com_ptr.Get(), 0U);
    }

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> const_buffer_com_ptr;
    UINT                                 slot;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
    using ConstantBuffer<C>::const_buffer_com_ptr;
    using Bindable::GetDeviceContext;

public:
    using ConstantBuffer<C>::ConstantBuffer;

    auto Bind(Graphics &graphics) noexcept -> void override
    {
        GetDeviceContext(graphics)->VSSetConstantBuffers(0U, 1u, const_buffer_com_ptr.GetAddressOf());
    }
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
    using ConstantBuffer<C>::const_buffer_com_ptr;
    using Bindable::GetDeviceContext;

public:
    using ConstantBuffer<C>::ConstantBuffer;

    auto Bind(Graphics &graphics) noexcept -> void override
    {
        GetDeviceContext(graphics)->PSSetConstantBuffers(0U, 1u, const_buffer_com_ptr.GetAddressOf());
    }
};

#endif //CONSTANT_BUFFER_H
