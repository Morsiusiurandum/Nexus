/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#include "Graphics.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <DirectXMath.h>
#include <array>
#include <d3d11.h>
#include <d3dcompiler.h>

namespace directx11
{
    Graphics::Graphics(HWND window, int width, int height)
        : width(width), height(height)
    {
        DXGI_SWAP_CHAIN_DESC swap_chain_desc               = {};
        swap_chain_desc.BufferDesc.Width                   = width;
        swap_chain_desc.BufferDesc.Height                  = height;
        swap_chain_desc.BufferDesc.Format                  = DXGI_FORMAT_B8G8R8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator   = 0;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 0;
        swap_chain_desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
        swap_chain_desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swap_chain_desc.SampleDesc.Count                   = 1;
        swap_chain_desc.SampleDesc.Quality                 = 0;
        swap_chain_desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.BufferCount                        = 1;
        swap_chain_desc.OutputWindow                       = window;
        swap_chain_desc.Windowed                           = TRUE;
        swap_chain_desc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
        swap_chain_desc.Flags                              = 0;

        UINT swapCreateFlags = 0u;

#ifndef NDEBUG
        swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        GRAPHICS_EXCEPTION(
            D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                swapCreateFlags,
                nullptr,
                0,
                D3D11_SDK_VERSION,
                &swap_chain_desc,
                &swap_chain,
                &device,
                nullptr,
                &device_context));

        // Use smart point to auto release
        Microsoft::WRL::ComPtr<ID3D11Resource> back_buffer;
        GRAPHICS_EXCEPTION(swap_chain->GetBuffer(0, _uuidof(ID3D11Resource), &back_buffer));
        GRAPHICS_EXCEPTION(device->CreateRenderTargetView(back_buffer.Get(), nullptr, &render_target_view));

        // create depth stencil state
        D3D11_DEPTH_STENCIL_DESC dsDesc = {};
        dsDesc.DepthEnable              = TRUE;
        dsDesc.DepthWriteMask           = D3D11_DEPTH_WRITE_MASK_ALL;
        dsDesc.DepthFunc                = D3D11_COMPARISON_LESS;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
        GRAPHICS_EXCEPTION(device->CreateDepthStencilState(&dsDesc, &pDSState));

        // bind depth state
        device_context->OMSetDepthStencilState(pDSState.Get(), 1u);

        // create depth stencil texture
        Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
        D3D11_TEXTURE2D_DESC                    descDepth = {};
        descDepth.Width                                   = width;
        descDepth.Height                                  = height;
        descDepth.MipLevels                               = 1u;
        descDepth.ArraySize                               = 1u;
        descDepth.Format                                  = DXGI_FORMAT_D32_FLOAT;
        descDepth.SampleDesc.Count                        = 1u;
        descDepth.SampleDesc.Quality                      = 0u;
        descDepth.Usage                                   = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags                               = D3D11_BIND_DEPTH_STENCIL;
        GRAPHICS_EXCEPTION(device->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

        // create view of depth stencil texture
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
        descDSV.Format                        = DXGI_FORMAT_D32_FLOAT;
        descDSV.ViewDimension                 = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice            = 0u;
        (device->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &depth_stencil_view_comptr));

        // bind depth stencil view to OM
        device_context->OMSetRenderTargets(1u, render_target_view.GetAddressOf(), depth_stencil_view_comptr.Get());

        // view port
        D3D11_VIEWPORT viewport;
        viewport.Width    = static_cast<float>(width);
        viewport.Height   = static_cast<float>(height);
        viewport.MinDepth = 0;
        viewport.MaxDepth = 1;
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        device_context->RSSetViewports(1U, &viewport);

        ImGui_ImplDX11_Init(device.Get(), device_context.Get());
    }

    Graphics::~Graphics()
    {
        ImGui_ImplDX11_Shutdown();
    }

    void Graphics::EndFrame()
    {

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        if (HRESULT hr; FAILED(hr = swap_chain->Present(1U, 0U)))
        {
            if (hr == DXGI_ERROR_DEVICE_REMOVED)
            {
                GRAPHICS_EXCEPTION(device->GetDeviceRemovedReason());
            }
            else
            {
                GRAPHICS_EXCEPTION(hr);
            }
        }
    }

    void Graphics::ClearBuffer(float r, float g, float b) noexcept
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        const std::array color = {r, g, b, 1.0f};

        device_context->ClearRenderTargetView(render_target_view.Get(), color.data());
        device_context->ClearDepthStencilView(depth_stencil_view_comptr.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0U);
    }

    void Graphics::DrawIndexed(UINT count)
    {
        device_context->DrawIndexed(count, 0u, 0u);
    }

    void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept
    {
        projection = proj;
    }

    auto Graphics::GetProjection() const noexcept -> DirectX::XMMATRIX
    {
        return projection;
    }

    void Graphics::SetCamera(DirectX::FXMMATRIX cam) noexcept
    {
        camera = cam;
    }

    DirectX::XMMATRIX Graphics::GetCamera() const noexcept
    {
        return camera;
    }

}
