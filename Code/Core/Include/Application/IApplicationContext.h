#pragma once
namespace Core
{
    class IApplicationContext
    {
    public:
        virtual int MessageLoop() = 0;
    };
}