#pragma once

#include <KEngine/engine_common.hpp>
#include <KEngine/macro_common.hpp>

namespace ke
{

inline Length Length::pixels(const std::uint32_t p_NumPixels)
{
    return ke::Length(p_NumPixels / s_ToPixelCoeff);
}

inline Length Length::metres(const double p_Meters)
{
    return ke::Length(p_Meters);
}

inline void Length::setPixelPerMeter(const std::uint32_t p_NumPixels, const double p_Meters)
{
    assert(p_NumPixels > 0);
    assert(p_Meters > 0.0);
    s_ToPixelCoeff = p_NumPixels / p_Meters;
}

inline Length::Length(void)
    : Length(0.0)
{}

inline Length::Length(ke::Length::Value p_Value)
    : Length(0.0)
{
    KE_UNUSED(p_Value);
}

inline Length::Length(const double p_LengthInMeters)
    : m_LengthInMetres(p_LengthInMeters)
{}

inline std::uint32_t Length::asPixels(void) const
{
    return static_cast<std::uint32_t>(this->asMetres() * Length::s_ToPixelCoeff);
}

inline double Length::asMetres(void) const
{
    return m_LengthInMetres;
}

inline bool operator==(const ke::Length p_Left, const ke::Length p_Right)
{
    return p_Left.asMetres() == p_Right.asMetres();
}

inline bool operator!=(const ke::Length p_Left, const ke::Length p_Right)
{
    return p_Left.asMetres() != p_Right.asMetres();
}

inline bool operator<(const ke::Length p_Left, const ke::Length p_Right)
{
    return p_Left.asMetres() < p_Right.asMetres();
}

inline bool operator>(const ke::Length p_Left, const ke::Length p_Right)
{
    return p_Left.asMetres() > p_Right.asMetres();
}

inline bool operator<=(const ke::Length p_Left, const ke::Length p_Right)
{
    return p_Left.asMetres() <= p_Right.asMetres();
}

inline bool operator>=(const ke::Length p_Left, const ke::Length p_Right)
{
    return p_Left.asMetres() >= p_Right.asMetres();
}

inline ke::Length operator-(const ke::Length p_Length)
{
    return ke::Length::metres(-1.0 * p_Length.asMetres());
}

inline ke::Length operator+(const ke::Length p_Left, const ke::Length p_Right)
{
    return ke::Length::metres(p_Left.asMetres() + p_Right.asMetres());
}

inline ke::Length & operator+=(ke::Length & p_Left, const ke::Length p_Right)
{
    return p_Left = p_Left + p_Right;
}

inline ke::Length operator-(const ke::Length p_Left, const ke::Length p_Right)
{
    return ke::Length::metres(p_Left.asMetres() - p_Right.asMetres());
}

inline ke::Length & operator-=(ke::Length & p_Left, const ke::Length p_Right)
{
    return p_Left = p_Left - p_Right;
}

inline ke::Length operator*(const ke::Length p_Left, const double p_Right)
{
    return ke::Length::metres(p_Left.asMetres()*p_Right);
}

inline ke::Length operator*(const ke::Length p_Left, const std::int64_t p_Right)
{
    return ke::Length::metres(p_Left.asMetres()*p_Right);
}

inline ke::Length operator*(const double p_Left, const ke::Length p_Right)
{
    return ke::Length::metres(p_Right.asMetres()*p_Left);
}

inline ke::Length operator*(const std::int64_t p_Left, const ke::Length p_Right)
{
    return ke::Length::metres(p_Right.asMetres()*p_Left);
}

inline ke::Length & operator*=(ke::Length & p_Left, const double p_Right)
{
    return p_Left = p_Left * p_Right;
}

inline ke::Length & operator*=(ke::Length & p_Left, const std::int64_t p_Right)
{
    return p_Left = p_Left * p_Right;
}

inline double operator/(ke::Length p_Left, const ke::Length p_Right)
{
    return p_Left.asMetres() / p_Right.asMetres();
}

inline ke::Length operator/(const ke::Length p_Left, const double p_Right)
{
    return ke::Length::metres(p_Left.asMetres() / p_Right);
}

inline ke::Length operator/(const ke::Length p_Left, const std::int64_t p_Right)
{
    return ke::Length::metres(p_Left.asMetres()*p_Right);
}

inline ke::Length & operator/=(ke::Length & p_rLeft, const double p_Right)
{
    return p_rLeft = p_rLeft / p_Right;
}

inline ke::Length & operator/=(ke::Length & p_rLeft, const std::int64_t p_Right)
{
    return p_rLeft = p_rLeft / p_Right;
}

inline ke::Length operator%(const ke::Length & p_rLeft, const ke::Length & p_rRight)
{
    return ke::Length::metres(std::fmod(p_rLeft.asMetres(), p_rRight.asMetres()));
}

} // KE ns