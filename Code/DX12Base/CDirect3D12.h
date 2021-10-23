#pragma once
#include "CGameObject.h"

class CDirect3D12 : public CGameObject
{
private:
    LPCWSTR m_wsAppName;
    BOOL    m_isFullScreen;
    BOOL    m_isVSyncEnable;
    POINT   m_ptScreenPos;
    POINT   m_ptScreenSize;
    FLOAT   m_fScreenDepth;
    FLOAT   m_fScreenNear;

    ID3D12Device* m_pDevice;
    ID3D12CommandQueue* m_commandQueue;
    char m_videoCardDescription[128];
    IDXGISwapChain3* m_swapChain;
    ID3D12DescriptorHeap* m_renderTargetViewHeap;
    ID3D12Resource* m_backBufferRenderTarget[2];
    unsigned int m_bufferIndex;
    ID3D12CommandAllocator* m_commandAllocator;
    ID3D12GraphicsCommandList* m_commandList;
    ID3D12PipelineState* m_pipelineState;
    ID3D12Fence* m_fence;
    HANDLE m_fenceEvent;
    unsigned long long m_fenceValue;

public:
    CDirect3D12();
    ~CDirect3D12();

    void InitWindow();
    BOOL InitDevice();
    void InitInstance(WNDPROC proc);

    virtual BOOL Render() override;
    virtual BOOL Release() override;
};

