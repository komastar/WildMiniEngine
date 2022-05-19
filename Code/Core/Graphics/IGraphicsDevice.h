#pragma once
#include "Common/RefCounter.h"

namespace Core
{
    class IWindow;
    class IGraphicsDevice : public RefCounter
    {
    public:
        virtual void Create(IWindow* window) = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
    };
}