#pragma once
#ifdef _WIN32
#include "IApplicationContext.h"

namespace Core
{
    class ApplicationContext : public IApplicationContext
    {
    public:
        virtual int MessageLoop() override;
    };
}
#endif // _WIN32
