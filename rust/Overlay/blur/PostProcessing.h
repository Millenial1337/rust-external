#pragma once

struct ImDrawList;

struct IDirect3DDevice9;

namespace PostProcessing
{
    void setDevice(IDirect3DDevice9* device) noexcept;
    void clearBlurTextures() noexcept;
    void onDeviceReset() noexcept;
    void newFrame() noexcept;
    void performFullscreenBlur(ImDrawList* drawList, float alpha) noexcept;
    void performFullscreenChromaticAberration(ImDrawList* drawList, float amount) noexcept;
    void performFullscreenMonochrome(ImDrawList* drawList, float amount) noexcept;
}
