#pragma once
#include "../Common/Geometry.hpp"
#include "../Common/Angle.hpp"

namespace ke
{

/** \class Transform2D

    A simple 2D transform object of which contains 2 translations from origin (x & y) and an angle of rotation.

*/
class Transform2D
{
public:
    using Translation1DType = double;
    using Translation2DType = ke::Vec2;

private:
    Translation2DType   m_Translation   = Translation2DType(0.0, 0.0);
    ke::Angle           m_Rotation      = ke::Angle::Zero;

public:
    Transform2D(const Translation2DType p_Translation = Translation2DType(0.0, 0.0), const ke::Angle p_Ang = ke::Angle::Zero);
    Transform2D(const Translation1DType p_TransX, const Translation1DType p_TransY, const ke::Angle p_Ang);
    Transform2D(const Transform2D & p_rTransform) = default;
    Transform2D & operator=(const Transform2D & p_rTransform) = default;
    ~Transform2D(void) = default;

    /** Return the 2D translation/postion in a ke::Vec2 (glm::dvec2). */
    Translation2DType getTranslation(void) const;
    /** Return the 2D rotation in ke::Angle. */
    ke::Angle getRotation(void) const;

    Transform2D & setTranslation(const Translation1DType p_TransX, const Translation1DType p_TransY);
    Transform2D & setTranslation(const Translation2DType p_Translation);
    Transform2D & setTranslation(const Transform2D & p_rTransform2D);
    Transform2D & setTranslationX(const Translation1DType p_NewX);
    Transform2D & setTranslationY(const Translation1DType p_NewY);

    Transform2D & setRotation(const ke::Angle p_Ang);
    Transform2D & setRotation(const Transform2D & p_rTransform2D);

}; // Transform2D class

extern Transform2D operator+(const Transform2D & p_rLeft, const Transform2D & p_rRight);
extern Transform2D operator+(const Transform2D & p_rTransform, const ke::Angle p_Ang);
extern Transform2D operator+(const ke::Angle p_Ang, const Transform2D & p_rTransform);
extern Transform2D operator+(const Transform2D::Translation2DType & p_rTranslation, const Transform2D & p_rTransform);
extern Transform2D operator+(const Transform2D & p_rTransform, const Transform2D::Translation2DType & p_rTranslation);
extern Transform2D & operator+=(Transform2D & p_rTransform, const ke::Angle & p_rAng);
extern Transform2D operator-(const Transform2D & p_rTransform);
extern Transform2D operator-(const Transform2D & p_rLeft, const Transform2D & p_rRight);
extern Transform2D operator-(const Transform2D & p_rTransform, const ke::Angle p_Ang);
extern Transform2D operator-(const Transform2D & p_rTransform, const Transform2D::Translation2DType & p_rTranslation);
extern Transform2D & operator-=(Transform2D & p_rTransform, const Transform2D::Translation2DType & p_tTranslation);
extern Transform2D operator*(const Transform2D & p_rLeft, const Transform2D & p_rRight);
extern Transform2D operator*(const Transform2D & p_rTransform, const double p_Scalar);
extern Transform2D operator*(const double p_Scalar, const Transform2D & p_rTransform);
extern Transform2D & operator*=(Transform2D & p_rTransform, const double p_Scalar);
extern Transform2D operator/(const Transform2D & p_rTransform, const double p_Scalar);
extern Transform2D & operator/=(Transform2D & p_rTransform, const double p_Scalar);

} // KE ns
