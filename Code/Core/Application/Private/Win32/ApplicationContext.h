#pragma once
#if defined(_WIN32)
#include "../../IApplicationContext.h"

namespace Core
{
    class ApplicationContext : public IApplicationContext
    {
        virtual int MessageLoop() override;
    };
}
#endif // _WIN32
