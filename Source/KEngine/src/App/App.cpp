#include "../../include/App/App.hpp"

namespace ke
{

AppUPtr    App::s_upApp(nullptr);

bool App::isReady(void)
{
    return s_upApp != nullptr;
}

KEApp & App::getSingleton(void)
{
    if (!App::isReady()) // App not instantiated.
    {
        ke::Debug::printError("App::Get : application not ready!");
        assert(false);
    }
    return *s_upApp;
}

void App::setSingleton(KEApp * const p_pApp)
{
    if (!p_pApp)
    {
        ke::Debug::printWarning("App::Set : Setting global App instance to nullptr...");
        return;
    }
    if (s_upApp)
    {
        ke::Debug::printWarning("App::Set : Already instantiated. Previous one will be freed first.");
        App::getSingleton().setQuitting(true);
        App::free();
    }
    s_upApp = AppUPtr(p_pApp);
}

void App::update(const ke::Time & p_rTime)
{
    if (App::isReady())
        s_upApp->updateApp(p_rTime);
    else
    {
        ke::Debug::printWarning("App::Update : invalid pointer to App...");
        assert(false);
    }
}

bool App::initialise(void)
{
    if (!App::isReady()) // App not instantiated.
    {
        ke::Debug::printError("App::Init : application not ready!");
        assert(false);
    }

    return s_upApp->initialise();
}

void App::free(void)
{
    // deprecated: maybe used as a manual call to free resources held by internal global KEApp instance?
}


} // KE ns