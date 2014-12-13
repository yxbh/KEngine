#pragma once

#include "../macro_common.hpp"

#include "Geometry.hpp"

namespace ke
{

inline ke::Angle Angle::radians(const double p_AngRad)
{
    return Angle(p_AngRad);
}

inline ke::Angle Angle::degrees(const double p_AngDeg)
{
    return Angle(p_AngDeg * (ke::maths::Pi/180));
}


inline Angle::Angle(const Value p_Value)
    : m_AngleInRadians(0.0)
{
    KE_UNUSED(p_Value);
}

inline double Angle::asRadians(void) const
{
    return m_AngleInRadians;
}

inline double Angle::asDegrees(void) const
{
    return m_AngleInRadians * (180 / ke::maths::Pi);
}

inline Angle::Angle(const double p_AngInRadian)
    : m_AngleInRadians(p_AngInRadian)
{}

inline bool operator==(const ke::Angle p_Left, const ke::Angle p_Right)
{
    return p_Left.asRadians() == p_Right.asRadians();
}

inline bool operator!=(const ke::Angle p_Left, const ke::Angle p_Right)
{
    return p_Left.asRadians() != p_Right.asRadians();
}

inline bool operator>=(const ke::Angle p_Left, const ke::Angle p_Right)
{
    return p_Left.asRadians() >= p_Right.asRadians();
}

inline bool operator<=(const ke::Angle p_Left, const ke::Angle p_Right)
{
    return p_Left.asRadians() <= p_Right.asRadians();
}

inline bool operator>(const ke::Angle p_Left, const ke::Angle p_Right)
{
    return p_Left.asRadians() > p_Right.asRadians();
}

inline bool operator<(const ke::Angle p_Left, const ke::Angle p_Right)
{
    return p_Left.asRadians() < p_Right.asRadians();
}

inline ke::Angle operator-(const ke::Angle p_Angle)
{
    return ke::Angle::radians(-1.0 * p_Angle.asRadians());
}

inline ke::Angle operator+(const ke::Angle p_Left, const ke::Angle p_Right)
{
    return ke::Angle::radians(p_Left.asRadians() + p_Right.asRadians());
}

inline ke::Angle operator-(const ke::Angle p_Left, const ke::Angle p_Right)
{
    return ke::Angle::radians(p_Left.asRadians() - p_Right.asRadians());
}

inline ke::Angle & operator+=(ke::Angle & p_rLeft, const ke::Angle p_Right)
{
    return p_rLeft = p_rLeft + p_Right;
}

inline ke::Angle & operator-=(ke::Angle & p_rLeft, const ke::Angle p_Right)
{
    return p_rLeft = p_rLeft - p_Right;
}

inline ke::Angle operator*(const ke::Angle p_Ang, const int64_t p_Scalar)
{
    return ke::Angle::radians(p_Ang.asRadians() * p_Scalar);
}

inline ke::Angle operator*(const ke::Angle p_Ang, const double p_Scalar)
{
    return ke::Angle::radians(p_Ang.asRadians() * p_Scalar);
}

inline ke::Angle operator*(const double p_Scalar, const ke::Angle p_Ang)
{
    return ke::Angle::radians(p_Ang.asRadians() * p_Scalar);
}

inline ke::Angle operator*(const int64_t p_Scalar, const ke::Angle p_Ang)
{
    return ke::Angle::radians(p_Ang.asRadians() * p_Scalar);
}

inline ke::Angle & operator*=(ke::Angle & p_rAng, const int64_t p_Scalar)
{
    return p_rAng = p_rAng * p_Scalar;
}

inline ke::Angle & operator*=(ke::Angle & p_rAng, const double p_Scalar)
{
    return p_rAng = p_rAng * p_Scalar;
}

inline double operator/(const ke::Angle p_Left, const ke::Angle p_Right)
{
    return p_Left.asRadians() / p_Right.asRadians();
}

inline ke::Angle operator/(const ke::Angle p_Ang, const int64_t p_Scalar)
{
    return ke::Angle::radians(p_Ang.asRadians() / p_Scalar);
}

inline ke::Angle operator/(const ke::Angle p_Ang, const double p_Scalar)
{
    return ke::Angle::radians(p_Ang.asRadians() / p_Scalar);
}

inline ke::Angle & operator/=(ke::Angle & p_rAng, const int64_t p_Scalar)
{
    return p_rAng = p_rAng / p_Scalar;
}

inline ke::Angle & operator/=(ke::Angle & p_rAng, const double p_Scalar)
{
    return p_rAng = p_rAng / p_Scalar;
}

inline ke::Angle operator%(const ke::Angle p_Left, const ke::Angle p_Right)
{
    return ke::Angle::radians(std::fmod(p_Left.asRadians(), p_Right.asRadians()));
}

} // KE ns
