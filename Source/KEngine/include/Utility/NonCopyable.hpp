#pragma once

namespace ke
{

/** \class NonCopyable
*/
class NonCopyable
{
public:
    NonCopyable(void) = default;
    NonCopyable(const ke::NonCopyable &) = delete;
    ke::NonCopyable & operator=(const NonCopyable &) = delete;
    virtual ~NonCopyable(void) {};

};

} // KE ns