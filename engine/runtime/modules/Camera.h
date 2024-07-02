/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <DirectXMath.h>

class Camera
{
public:
    [[nodiscard]] auto GetMatrix() const noexcept -> DirectX::XMMATRIX;

    void SpawnControlWindow() noexcept;

    void Reset() noexcept;

private:
    float r     = 20.0f;
    float theta = 0.0f;
    float phi   = 0.0f;
    float pitch = 0.0f;
    float yaw   = 0.0f;
    float roll  = 0.0f;

public:
    unsigned int clear_flag;
};

#endif //CAMERA_H
