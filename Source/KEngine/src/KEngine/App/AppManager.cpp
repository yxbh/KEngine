#include <KEngine/App/AppManager.hpp>

namespace ke
{

AppUptr    AppManager::s_upApp(nullptr);

bool AppManager::isReady(void)
{
    return s_upApp != nullptr;
}

App & AppManager::getSingleton(void)
{
    if (!AppManager::isReady()) // App not instantiated.
    {
        ke::Debug::printError("App::Get : application not ready!");
        assert(false);
        throw std::logic_error("App::getSingleton() : pointer to app object invalid.");
    }
    return *s_upApp;
}

void AppManager::setSingleton(App * const p_pApp)
{
    if (!p_pApp)
    {
        ke::Debug::printWarning("App::Set : Setting global App instance to nullptr...");
        return;
    }
    if (s_upApp)
    {
        ke::Debug::printWarning("App::Set : Already instantiated. Previous one will be freed first.");
        AppManager::getSingleton().setQuitting(true);
        AppManager::free();
    }
    s_upApp = AppUptr(p_pApp);
}

void AppManager::update(const ke::Time & p_rTime)
{
    if (AppManager::isReady())
        s_upApp->updateApp(p_rTime);
    else
    {
        ke::Debug::printWarning("App::update : invalid pointer to App.");
        assert(false);
    }
}

void AppManager::render(const ke::Time & p_rTime)
{
    if (AppManager::isReady())
        s_upApp->renderApp(p_rTime);
    else
    {
        ke::Debug::printError("App::render : invalid pointer to App.");
    }
}

bool AppManager::initialise(void)
{
    if (!AppManager::isReady()) // App not instantiated.
    {
        ke::Debug::printError("App::Init : application not ready!");
        assert(false);
    }

    return s_upApp->initialise();
}

void AppManager::free(void)
{
    // deprecated: maybe used as a manual call to free resources held by internal global KEApp instance?
}


} // KE ns