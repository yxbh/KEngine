#pragma once
#include <cmath>
#include <cstdint>

namespace ke
{

/** \class Angle
    \brief A unit class representing an angle measurement.
*/
class Angle
{

public:
    enum class Value
    {
        Zero
    };
    static const Angle Zero;
    using AngleType = double;       // type used to define internal representation (physical type).

private:
    double  m_AngleInRadians; /** The internal value of the angle object. */

public:
    /** Construct an Angle object representing \a p_AngRad radians. */
    static Angle radians(const double p_AngRad);
    /** Construct an Angle object representing \a p_AngDeg degrees. */
    static Angle degrees(const double p_AngDeg);

    /** Ctor. Construct an Angle object which represents 0 degrees. */
    Angle(void) = default;
    /** Construct an Angle object of \a p_Value degrees. */
    Angle(const Value p_Value);

    /** @return the angle value in radian. */
    double asRadians(void) const;
    /** @return the angle value in degrees. */
    double asDegrees(void) const;

    /** Normalise the angle to [0-360] degrees. */
    Angle & normalise(const ke::Angle p_UpperWrapVal = Angle::degrees(180), const ke::Angle p_LowerWrapVal = Angle::degrees(-180));

private:
    /** A private constructor used internally. */
    explicit Angle(const double p_AngInRadian);

}; // Angle class

bool        operator== (const ke::Angle p_Left, const ke::Angle p_Right);
bool        operator!= (const ke::Angle p_Left, const ke::Angle p_Right);
bool        operator>= (const ke::Angle p_Left, const ke::Angle p_Right);
bool        operator<= (const ke::Angle p_Left, const ke::Angle p_Right);
bool        operator> (const ke::Angle p_Left, const ke::Angle p_Right);
bool        operator< (const ke::Angle p_Left, const ke::Angle p_Right);
ke::Angle   operator- (const ke::Angle p_Angle);
ke::Angle   operator+ (const ke::Angle p_Left, const ke::Angle p_Right);
ke::Angle   operator- (const ke::Angle p_Left, const ke::Angle p_Right);
ke::Angle & operator+= (ke::Angle & p_rLeft, const ke::Angle p_Right);
ke::Angle & operator-= (ke::Angle & p_rLeft, const ke::Angle p_Right);
ke::Angle   operator* (const ke::Angle p_Ang, const int64_t p_Scalar);
ke::Angle   operator* (const ke::Angle p_Ang, const double p_Scalar);
ke::Angle   operator* (const double p_Scalar, const ke::Angle p_Ang);
ke::Angle   operator* (const int64_t p_Scalar, const ke::Angle p_Ang);
ke::Angle & operator*= (ke::Angle & p_rAng, const int64_t p_Scalar);
ke::Angle & operator*= (ke::Angle & p_rAng, const double p_Scalar);
double      operator/ (const ke::Angle p_Left, const ke::Angle p_Right);
ke::Angle   operator/ (const ke::Angle p_Ang, const int64_t p_Scalar);
ke::Angle   operator/ (const ke::Angle p_Ang, const double p_Scalar);
ke::Angle & operator/= (ke::Angle & p_rAng, const int64_t p_Scalar);
ke::Angle & operator/= (ke::Angle & p_rAng, const double p_Scalar);
ke::Angle   operator% (const ke::Angle p_Left, const ke::Angle p_Right);

} // KE ns

#include "Angle.inl"
