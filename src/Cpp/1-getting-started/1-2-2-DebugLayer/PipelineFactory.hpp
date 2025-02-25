#pragma once

#include "Definitions.hpp"
#include "VertexType.hpp"
#include "Pipeline.hpp"

#include <d3d11_2.h>

#include <unordered_map>
#include <string_view>
#include <memory>

struct PipelineDescriptor
{
    std::wstring VertexFilePath;
    std::wstring PixelFilePath;
    VertexType VertexType;
};

class PipelineFactory
{
public:
    PipelineFactory(const WRL::ComPtr<ID3D11Device>& device);

    bool CreatePipeline(
        const PipelineDescriptor& settings,
        std::unique_ptr<Pipeline>& pipeline);

private:
    [[nodiscard]] WRL::ComPtr<ID3D11VertexShader> CreateVertexShader(
        const std::wstring& filePath,
        WRL::ComPtr<ID3DBlob>& vertexShaderBlob) const;
    [[nodiscard]] WRL::ComPtr<ID3D11PixelShader> CreatePixelShader(const std::wstring& filePath) const;

    bool CreateInputLayout(
        const VertexType layoutInfo,
        const WRL::ComPtr<ID3DBlob>& vertexBlob,
        WRL::ComPtr<ID3D11InputLayout>& inputLayout);

    bool CompileShader(
        const std::wstring& filePath,
        const std::string& entryPoint,
        const std::string& profile,
        WRL::ComPtr<ID3DBlob>& shaderBlob) const;

    WRL::ComPtr<ID3D11Device> _device = nullptr;
    std::unordered_map<VertexType, std::vector<D3D11_INPUT_ELEMENT_DESC>> _layoutMap;
};
