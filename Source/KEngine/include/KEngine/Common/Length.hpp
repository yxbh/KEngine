#pragma once
#include <cstdint>
#include <cmath>

namespace ke
{

/** \class Length

    A unit class to facilitate pixel unit conversions.

*/
class Length
{
public:
    enum class Value
    {
        Zero
    };
    static const Length Zero;
    static double s_ToPixelCoeff; // pixels = m_LengthInMeters * s_ToPixelCoeff

private:
    double  m_LengthInMetres;

public:
    static Length pixels(const std::uint32_t p_NumPixels);
    static Length metres(const double p_Meters);
    static void setPixelPerMeter(const std::uint32_t p_NumPixels, const double p_Meters);

    Length(void);
    Length(Value);

    std::uint32_t asPixels(void) const;
    double asMetres(void) const;

private:
    explicit Length(const double p_LengthInMeters);

};

bool operator==(const ke::Length p_Left, const ke::Length p_Right);
bool operator!=(const ke::Length p_Left, const ke::Length p_Right);
bool operator<(const ke::Length p_Left, const ke::Length p_Right);
bool operator>(const ke::Length p_Left, const ke::Length p_Right);
bool operator<=(const ke::Length p_Left, const ke::Length p_Right);
bool operator>=(const ke::Length p_Left, const ke::Length p_Right);
ke::Length operator-(const ke::Length p_Length);
ke::Length operator+(const ke::Length p_Left, const ke::Length p_Right);
ke::Length & operator+=(ke::Length & p_Left, const ke::Length p_Right);
ke::Length operator-(const ke::Length p_Left, const ke::Length p_Right);
ke::Length & operator-=(ke::Length & p_Left, const ke::Length p_Right);
ke::Length operator*(const ke::Length p_Left, const double p_Right);
ke::Length operator*(const ke::Length p_Left, const std::int64_t p_Right);
ke::Length operator*(const double p_Left, const ke::Length p_Right);
ke::Length operator*(const std::int64_t p_Left, const ke::Length p_Right);
ke::Length & operator*=(ke::Length & p_Left, const double p_Right);
ke::Length & operator*=(ke::Length & p_Left, const std::int64_t p_Right);
double operator/(ke::Length p_Left, const ke::Length p_Right);
ke::Length operator/(const ke::Length p_Left, const double p_Right);
ke::Length operator/(const ke::Length p_Left, const std::int64_t p_Right);
ke::Length & operator/=(ke::Length & p_rLeft, const double p_Right);
ke::Length & operator/=(ke::Length & p_rLeft, const std::int64_t p_Right);
ke::Length operator%(const ke::Length & p_rLeft, const ke::Length & p_rRight);

} // KE ns

#include "Length.inl"