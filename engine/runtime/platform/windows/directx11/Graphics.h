/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../exception/GraphicsException.h"
#include "../windows_platform_macro.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl.h>

#define GRAPHICS_EXCEPTION(hr)  \
    if (hr != SEVERITY_SUCCESS) \
    throw GraphicsException(__LINE__, __FILE__, hr)

namespace directx11
{
    class Graphics
    {
        friend class Bindable;

    public:
        /**
         * \brief Default constructor
         * \param window current window pointer
         */
        explicit Graphics(HWND window, int width, int height);
        ~ Graphics();

        explicit Graphics(const Graphics &)                = delete;
        auto     operator=(const Graphics &) -> Graphics & = delete;

        /**
         * \brief End current frame
         */
        void EndFrame();

        void ClearBuffer(float r, float g, float b) noexcept;

        void DrawIndexed(UINT count);

        void SetProjection(DirectX::FXMMATRIX proj) noexcept;

        auto GetProjection() const noexcept -> DirectX::XMMATRIX;

        void SetCamera(DirectX::FXMMATRIX cam) noexcept;
        auto GetCamera() const noexcept -> DirectX::XMMATRIX;
        void EnableImgui() noexcept;
        void DisableImgui() noexcept;
        bool IsImguiEnabled() const noexcept;

    private:
        DirectX::XMMATRIX projection{};
        DirectX::XMMATRIX camera{};

        Microsoft::WRL::ComPtr<ID3D11Device>           device;
        Microsoft::WRL::ComPtr<IDXGISwapChain>         swap_chain;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>    device_context;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view_comptr;

        int width, height;
    };
}

#endif // GRAPHICS_H
