#include "../../include/Dev/dbg.hpp"
#include <thread>
#include <chrono>


namespace ke
{

bool Debug::s_PauseOnError(true);
bool Debug::s_PuaseOnWarning(false);

void Debug::print(const MsgType p_MsgType, const std::string & p_rMsg)
{
#if defined _DEBUG || defined KE_DEBUG
    std::string msg("DBG("); msg.reserve(100);
    switch (p_MsgType)
    {
    case DBG_OK:
    case DBG_DEFAULT:
        msg += "OK";    break;
    case DBG_WARNING:
        msg += "WARN"; break;
    case DBG_ERROR:
        msg += "ERROR"; break;
    case DBG_FATAL:
        msg += "FATAL"; break;
    default:
        msg += "UNKNOWN";
    }
    msg += "): "; msg += p_rMsg; msg += '\n';
    if (p_MsgType == DBG_ERROR || p_MsgType == DBG_ERROR)
        std::cerr << msg;
    else
        std::clog << msg;
#else
    DBG_PRINT_IGNORE(p_MsgType); DBG_PRINT_IGNORE(p_rMsg);
#endif
}

void Debug::print(const std::string & p_rMsg)
{
    return print(MsgType::DBG_DEFAULT, p_rMsg);
}

void Debug::printWarning(const std::string & p_rMsg)
{
    print(MsgType::DBG_WARNING, p_rMsg);
    if (s_PuaseOnWarning)
        Debug::pause();
}

void Debug::printError(const std::string & p_rMsg)
{
    print(MsgType::DBG_ERROR, p_rMsg);
    if (s_PauseOnError)
        Debug::pause();
}

void Debug::printFatalError(const std::string & p_rMsg)
{
    print(MsgType::DBG_ERROR, p_rMsg);
    if (s_PauseOnError)
        Debug::pause();
    exit(EXIT_FAILURE);
}

void Debug::clearConsole(void)
{
#if defined(_WIN32) || defined(_WIN64)
    system("CLS");
#else
    for (int i = 0; i < 20; ++i) // not tested.
        std::clog << '\n';
    std::clog.flush();
#endif
}

void Debug::pause(void)
{
#if defined(_WIN32) || defined(_WIN64)
    ke::Debug::print("Pausing application. Press Enter to continue...");
    system("Pause");
#else
    ke::Debug::printWarning(" thread sleep : 60 seconds...");
    std::this_thread::sleep_for(std::chrono::seconds(60));
#endif
}

void Debug::setPauseOnWarning(const bool p_Pause)
{
    s_PuaseOnWarning = p_Pause;
}

void Debug::setPauseOnError(const bool p_Pause)
{
    s_PauseOnError = p_Pause;
}

} // KE ns
