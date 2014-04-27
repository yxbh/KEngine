#pragma once
#include <cstdint>
#define KE_UNREFERENCED_PARAMETER(X) X

namespace ke
{

/** \class Time
    A class which defines a period of time (a Time). The Time can be netgative.
    The Time can be evalued to abirtary precision (seconds(double), milliseconds(in32) and microseconds(int64).

    Modeled after sf::Time.
*/
class Time
{
public:
    enum class Value
    {
        Zero
    };
    static const Time Zero;

private:
    std::int64_t    m_TimeInMicroseconds = 0;

public:
    Time(void) = default;
    Time(const Value p_Value);
    const double asSeconds(void) const;
    const std::int32_t asMilliseconds(void) const;
    const std::int64_t asMicroseconds(void) const;

    static ke::Time seconds(const double p_Amount);
    static ke::Time milliseconds(const std::int32_t p_Amount);
    static ke::Time microseconds(const std::int64_t p_Amount);

private:
    explicit Time(const std::int64_t p_Microseconds);

};

bool operator==(const ke::Time p_Left, const ke::Time p_Right);
bool operator!=(const ke::Time p_Left, const ke::Time p_Right);
bool operator<(const ke::Time p_Left, const ke::Time p_Right);
bool operator>(const ke::Time p_Left, const ke::Time p_Right);
bool operator<=(const ke::Time p_Left, const ke::Time p_Right);
bool operator>=(const ke::Time p_Left, const ke::Time p_Right);
ke::Time operator-(const ke::Time p_Time);
ke::Time operator+(const ke::Time p_Left, const ke::Time p_Right);
ke::Time & operator+=(ke::Time & p_Left, const ke::Time p_Right);
ke::Time operator-(const ke::Time p_Left, const ke::Time p_Right);
ke::Time & operator-=(ke::Time & p_Left, const ke::Time p_Right);
ke::Time operator*(const ke::Time p_Left, const double p_Right);
ke::Time operator*(const ke::Time p_Left, const std::int64_t p_Right);
ke::Time operator*(const double p_Left, const ke::Time p_Right);
ke::Time operator*(const std::int64_t p_Left, const ke::Time p_Right);
ke::Time & operator*=(ke::Time & p_Left, const double p_Right);
ke::Time & operator*=(ke::Time & p_Left, const std::int64_t p_Right);
double operator/(ke::Time p_Left, const ke::Time p_Right);
ke::Time operator/(const ke::Time p_Left, const double p_Right);
ke::Time operator/(const ke::Time p_Left, const std::int64_t p_Right);
ke::Time & operator/=(ke::Time & p_rLeft, const double p_Right);
ke::Time & operator/=(ke::Time & p_rLeft, const std::int64_t p_Right);
ke::Time operator%(const ke::Time & p_rLeft, const ke::Time & p_rRight);

} // KE ns

#include "Time.inl"
