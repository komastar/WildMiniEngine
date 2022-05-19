#include "EditorApplication.h"
#include "Application/Platform/ApplicationContextFactory.h"
#include "Window/WindowContextFactory.h"
#include "Graphics/Platform/DeviceContextFactory.h"

EditorApplication::EditorApplication()
{
}

void EditorApplication::OnInitialize()
{
    window = Core::WindowContextFactory::Create();
    window->Create();
    window->Show();
    window->Focus();

    device = Core::DeviceContextFactory::Create();
    device->Create(window);

    context = Core::ApplicationContextFactory::Create(window, device);
}

void EditorApplication::OnTerminate()
{
}
