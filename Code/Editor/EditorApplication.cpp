#include "EditorApplication.h"
#include "Application/Platform/WMApplicationContextFactory.h"
#include "Window/Platform/WMWindowtFactory.h"
#include "Graphics/Platform/WMGraphicsDeviceFactory.h"

EditorApplication::EditorApplication()
{
}

void EditorApplication::OnInitialize()
{
    window = WildMini::Window::WMWindowtFactory::Create();
    window->Create();
    window->Show();
    window->Focus();

    device = WildMini::Graphics::WMGraphicsDeviceFactory::Create(window);

    context = WildMini::Application::WMApplicationContextFactory::Create(window, device);
}

void EditorApplication::OnTerminate()
{
}
