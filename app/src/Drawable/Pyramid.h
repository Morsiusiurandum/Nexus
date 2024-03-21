#ifndef PYRAMID_H
#define PYRAMID_H

#include "Drawable.h"
#include <random>

class Pyramid : public Drawable<Pyramid>
{
public:
    Pyramid(Graphics &gfx, std::mt19937 &rng,
            std::uniform_real_distribution<float> &adist,
            std::uniform_real_distribution<float> &ddist,
            std::uniform_real_distribution<float> &odist,
            std::uniform_real_distribution<float> &rdist);
    void              Update(float dt) noexcept override;
    auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override;

private:
    // positional
    float r;
    float roll  = 0.0f;
    float pitch = 0.0f;
    float yaw   = 0.0f;
    float theta;
    float phi;
    float chi;
    // speed (delta/s)
    float droll;
    float dpitch;
    float dyaw;
    float dtheta;
    float dphi;
    float dchi;
};
#endif //PYRAMID_H
