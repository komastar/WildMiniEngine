//
//  ApplicationContext.h
//  WMFramework
//
//  Created by Eugene Kim on 2022/06/06.
//

#pragma once
#ifdef __APPLE__
#include "Application/WMApplicationContext.h"
namespace WildMini::Application::Private
{
    class ApplicationContext : public WildMini::Application::WMApplicationContext
    {
    public:
        int MessageLoop() override;
    };
}
#endif /* __APPLE__ */
