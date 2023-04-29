//
//  ApplicationContext.h
//  WMFramework
//
//  Created by Eugene Kim on 2022/06/06.
//

#pragma once
#ifdef __APPLE__
#include "Application/WMApplicationContext.h"
namespace WildMini
{
    class ApplicationContext : public WMApplicationContext
    {
    public:
        int MessageLoop() override;
        virtual void Update() override {};
        virtual void Render() override {};
    };
}
#endif /* __APPLE__ */
