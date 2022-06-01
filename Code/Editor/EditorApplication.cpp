#include "EditorApplication.h"
#include "Application/Private/ApplicationContextFactory.h"
#include "Window/Private/WindowFactory.h"
#include "Graphics/Private/GraphicsDeviceFactory.h"

EditorApplication::EditorApplication()
{
}

void EditorApplication::OnInitialize()
{
    window = WildMini::Window::WindowFactory::Create();
    window->Create();
    window->Show();
    window->Focus();

    device = WildMini::Graphics::Private::GraphicsDeviceFactory::Create();
    device->CreateCommandList();
}

void EditorApplication::OnTerminate()
{
}
