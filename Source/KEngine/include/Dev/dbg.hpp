#pragma once
#include "../Utility/StaticClass.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

// macros
#define DBG_PRINT_IGNORE(X) X
#define KE_UNREFERENCED_PARAMETER( PARAMETER ) PARAMETER

namespace ke
{

class Debug
    : public ke::StaticClass
{
public:
    enum MsgType
    {
        DBG_DEFAULT = 0,
        DBG_OK      = 1,
        DBG_WARNING = 2,
        DBG_ERROR   = 3,
        DBG_FATAL   = 4,
    };

private:
    static bool s_PauseOnError;
    static bool s_PuaseOnWarning;

public:
    /** call print() with a specified debug output header.*/
    static void print(const MsgType p_MsgType, const std::string & p_rMsg);
    /** Print debug string to console with "Default" header.*/
    static void print(const std::string & p_rMsg);
    /** print debug string to console with warning header. */
    static void printWarning(const std::string & p_rMsg);
    /** print debug string to console with error header. */
    static void printError(const std::string & p_rMsg);
    /** print message to stderr and then exit. */
    static void printFatalError(const std::string & p_rMsg);
    /** Clear the console screen. */
    static void clearConsole(void);
    /** Pause applicatoin. */
    static void pause(void);
    /** */
    static void setPauseOnWarning(const bool p_Pause = true);
    /** */
    static void setPauseOnError(const bool p_Pause = true);
private:
    Debug(void) = delete;

};

} //KE ns