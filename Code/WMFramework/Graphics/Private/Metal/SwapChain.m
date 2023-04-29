//
//  SwapChain.m
//  WMFramework
//
//  Created by Eugene Kim on 2023/04/29.
//

#import <Foundation/Foundation.h>
#include "Graphics/Private/Metal/SwapChain.h"
 
using namespace WildMini;

SwapChain::SwapChain(CommandQueue* commandQueue, WMWindow* window)
{
}

SwapChain::~SwapChain()
{

}

const WMTexture* SwapChain::RenderTargetTexture() const
{
    return nullptr;
}

const WMTexture* SwapChain::DepthStencilTexture() const
{
    return nullptr;
}

void SwapChain::Resize(uint32_t width, uint32_t height)
{

}

void SwapChain::Present()
{ 
}
