#pragma once

#include "ResourceDescriptor.hpp"
#include "Definitions.hpp"

#include <d3d11_2.h>

#include <unordered_map>
#include <cstdint>

class Pipeline
{
public:
    friend class PipelineFactory;
    friend class DeviceContext;

    void BindTexture(uint32_t slotIndex, ID3D11ShaderResourceView* texture);
    void BindSampler(uint32_t slotIndex, ID3D11SamplerState* sampler);
    void BindVertexStageConstantBuffer(uint32_t slotIndex, ID3D11Buffer* buffer);
    void SetViewport(
        const float left,
        const float top,
        const float width,
        const float height);
    void SetDepthStencilState(ID3D11DepthStencilState* depthStencilState);

private:
    WRL::ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
    WRL::ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
    WRL::ComPtr<ID3D11InputLayout> _inputLayout = nullptr;
    WRL::ComPtr<ID3D11DepthStencilState> _depthStencilState = nullptr;
    std::unordered_map<ResourceDescriptor, ID3D11DeviceChild*> _resources;
    D3D11_PRIMITIVE_TOPOLOGY _primitiveTopology = {};
    uint32_t _vertexSize = 0;
    D3D11_VIEWPORT _viewport = {};
};
