#pragma once
#include "IApplication.h"
#include "ApplicationContext.h"

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