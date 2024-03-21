#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Exception/GraphicsException.h"
#include "NexusMacro.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl.h>

#define GRAPHICS_EXCEPTION(hr)  \
    if (hr != SEVERITY_SUCCESS) \
    throw GraphicsException(__LINE__, __FILE__, hr)

class Graphics
{
    friend class Bindable;

public:
    /**
     * @brief Default constructor
     * @param window current window pointer
     */
    explicit Graphics(HWND window);
    ~Graphics();

    explicit Graphics(const GraphicsException &)   = delete;
    auto operator=(const Graphics &) -> Graphics & = delete;

    /**
     * \brief End current frame
     */
    void EndFrame();

    void ClearBuffer(float r, float g, float b) noexcept;

    void DrawIndexed(UINT count);

    void SetProjection(DirectX::FXMMATRIX proj) noexcept;

    [[nodiscard]] auto GetProjection() const noexcept -> DirectX::XMMATRIX;

private:
    DirectX::XMMATRIX projection{};

    Microsoft::WRL::ComPtr<ID3D11Device>           device;
    Microsoft::WRL::ComPtr<IDXGISwapChain>         swap_chain;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>    device_context;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};

#endif // GRAPHICS_H
