/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef NEXUS_UTILS_COLOR_H_
#define NEXUS_UTILS_COLOR_H_

#define Colour Color

struct __declspec(dllexport) Color
{
private:
    unsigned int dword{};

public:
    constexpr Color() noexcept = default;

    constexpr Color(const Color &color) noexcept = default;

    constexpr explicit Color(unsigned int dw) noexcept;

    constexpr explicit Color(unsigned char x, unsigned char r, unsigned char g, unsigned char b) noexcept;

    constexpr explicit Color(unsigned char r, unsigned char g, unsigned char b) noexcept;

    constexpr explicit Color(Color col, unsigned char x) noexcept;

    auto operator=(Color color) noexcept -> Color &;

    [[nodiscard]] constexpr auto GetR() const noexcept -> unsigned char;

    [[nodiscard]] constexpr auto GetG() const noexcept -> unsigned char;

    [[nodiscard]] constexpr auto GetB() const noexcept -> unsigned char;

    [[nodiscard]] constexpr auto GetA() const noexcept -> unsigned char;

    void SetX(unsigned char x) noexcept;

    void SetA(unsigned char a) noexcept;

    void SetR(unsigned char r) noexcept;

    void SetG(unsigned char g) noexcept;

    void SetB(unsigned char b) noexcept;
};

#endif //NEXUS_UTILS_COLOR_H_
