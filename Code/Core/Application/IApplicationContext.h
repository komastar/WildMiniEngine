#pragma once
#include "Common/RefCounter.h"

namespace Core
{
    class IWindow;
    class IGraphicsDevice;
    class IApplicationContext : public RefCounter
    {
    public:
        virtual int MessageLoop() = 0;

    protected:
        IGraphicsDevice* device;
        IWindow* window;
    };
}
