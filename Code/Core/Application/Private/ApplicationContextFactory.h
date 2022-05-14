#pragma once
#include "../IApplication.h"
#include "Win32/ApplicationContext.h"

namespace Core
{
    class ApplicationContextFactory
    {
    public:
        static IApplicationContext* Create()
        {
            return new ApplicationContext();
        }
    };
}