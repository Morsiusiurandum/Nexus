/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef NEXUS_WINDOW_H
#define NEXUS_WINDOW_H

#include <memory>

#include "../../core/utils/Timer.h"
#include "../../include/NexusIO.h"
#include "directx11/Graphics.h"
#include "exception/WindowException.h"
#include "windows_platform_macro.h"

//helper macro
#define NEXUS_EXCEPT(hr) WindowException(__LINE__, __FILE__, hr)
#define NEXUS_LAST_EXCEPT() WindowException(__LINE__, __FILE__, GetLastError())

class Window
{
private:
    class WindowClass
    {
    public:
        static auto GetName() noexcept -> const WCHAR *;

        static auto GetInstance() noexcept -> HINSTANCE;

        WindowClass(const WindowClass &) = delete;

        auto operator=(const WindowClass &) -> WindowClass & = delete;

    private:
        WindowClass() noexcept;

        ~WindowClass();

        static constexpr auto wndClassName = "Nexus Direct3D Engine";

        static WindowClass wndClass;

        HINSTANCE hInst;
    };

public:
    /**
     * @brief Initialization window
     * @param width window width
     * @param height window height
     * @param name window name
     */
    Window(int width, int height, const WCHAR *name);

    Window(const Window &) = delete;

    auto operator=(const Window &) -> Window & = delete;

    ~ Window();

    [[nodiscard]] static auto ProcessMessage() noexcept -> std::optional<int>;

    // [[nodiscard]] auto GetGraphics() -> directx11::Graphics &;

private:
    [[nodiscard]] auto HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

    static auto CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

    static auto CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

public:
    keyboard keyboard;
    Mouse    mouse;

    int width{}, height{};

    HWND h_wnd;

};

#endif //NEXUS_WINDOW_H
