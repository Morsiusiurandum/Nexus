#include "Box.h"
#include "BindableBase.h"
#include "Cube.h"
#include <DirectXMath.h>

Box::Box(Graphics                              &gfx,
         std::mt19937                          &rng,
         std::uniform_real_distribution<float> &adist,
         std::uniform_real_distribution<float> &ddist,
         std::uniform_real_distribution<float> &odist,
         std::uniform_real_distribution<float> &rdist,
         std::uniform_real_distribution<float> &bdist,
         DirectX::XMFLOAT3                      material)
    : Object(gfx, rng, adist, ddist, odist, rdist)
{
    namespace dx = DirectX;

    if (!IsStaticInitialized())
    {
        struct Vertex
        {
            dx::XMFLOAT3 pos;
            dx::XMFLOAT3 n;
        };

        auto model = Cube::MakeIndependent<Vertex>();
       model.SetNormalsIndependentFlat();

        AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertex));

        auto pvs   = std::make_unique<VertexShader>(gfx, L"shader/VertexShader.cso");
        auto pvsbc = pvs->GetBytecode();
        AddStaticBind(std::move(pvs));

        AddStaticBind(std::make_unique<PixelShader>(gfx, L"shader/PixelShader.cso"));

        AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.index));

        struct ConstantBuffer2
        {
            struct
            {
                float r;
                float g;
                float b;
                float a;
            } face_colors[6];
        };
        const ConstantBuffer2 cb2 =
            {
                {
                 {1.0f, 0.0f, 1.0f},
                 {1.0f, 0.0f, 0.0f},
                 {0.0f, 1.0f, 0.0f},
                 {0.0f, 0.0f, 1.0f},
                 {1.0f, 1.0f, 0.0f},
                 {0.0f, 1.0f, 1.0f},
                 }
        };
        AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2 ));
    
        
        const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
             //   {"Normal",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

        AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
    }
    else
    {
        SetIndexFromStatic();
    }

    AddBind(std::make_unique<TransformCbuf>(gfx, *this));
    
    /*
    struct PSMaterialConstant
    {
        alignas(16) dx::XMFLOAT3 color{};
        float specularIntensity = 0.6f;
        float specularPower     = 30.0f;
        float padding[2]{};
    } colorConst;

    colorConst.color = material;

    AddBind(std::make_unique<PixelConstantBuffer<PSMaterialConstant>>(gfx, colorConst, 1u));
*/
   
    // model deformation transform (per instance, not stored as bind)
    dx::XMStoreFloat3x3(
        &mt,
        dx::XMMatrixScaling(1.0f, 1.0f, bdist(rng)));
}

auto Box::GetTransformXM() const noexcept -> DirectX::XMMATRIX
{
      return DirectX::XMLoadFloat3x3(&mt) * Object::GetTransformXM();
}
