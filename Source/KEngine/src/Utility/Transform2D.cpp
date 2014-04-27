#include "../../include/Utility/Transform2D.hpp"

namespace ke
{

Transform2D::Transform2D(const Transform2D::Translation2DType p_Translation, const ke::Angle p_Ang)
    : m_Translation(p_Translation), m_Rotation(p_Ang)
{}

Transform2D::Transform2D(const double p_TransX, const double p_TransY, const ke::Angle p_Ang)
    : Transform2D(Translation2DType(p_TransX, p_TransY), p_Ang)
{}

Transform2D::Translation2DType Transform2D::GetTranslation(void) const
{
    return m_Translation;
}

ke::Angle Transform2D::GetRotation(void) const
{
    return m_Rotation;
}

Transform2D & Transform2D::SetTranslation(const double p_TransX, const double p_TransY)
{
    m_Translation.x = p_TransX; m_Translation.y = p_TransY;
    return *this;
}

Transform2D & Transform2D::SetTranslation(const Translation2DType p_Translation)
{
    m_Translation = p_Translation;
    return *this;
}

Transform2D & Transform2D::SetTranslation(const Transform2D & p_rTransform2D)
{
    m_Translation = p_rTransform2D.GetTranslation();
    return *this;
}

Transform2D & Transform2D::SetTranslationX(const Translation1DType p_NewX)
{
    m_Translation.x = p_NewX;
    return *this;
}

Transform2D & Transform2D::SetTranslationY(const Translation1DType p_NewY)
{
    m_Translation.y = p_NewY;
    return *this;
}

Transform2D & Transform2D::SetRotation(const ke::Angle p_Ang)
{
    m_Rotation = p_Ang;
    return *this;
}

Transform2D & Transform2D::SetRotation(const Transform2D & p_rTransform2D)
{
    m_Rotation = p_rTransform2D.GetRotation();
    return *this;
}

Transform2D operator+(const Transform2D & p_rLeft, const Transform2D & p_rRight)
{
    return Transform2D(p_rLeft.GetTranslation() + p_rRight.GetTranslation(), p_rLeft.GetRotation() + p_rRight.GetRotation());
}

Transform2D operator+(const Transform2D & p_rTransform, const ke::Angle p_Ang)
{
    return Transform2D(p_rTransform.GetTranslation(), p_rTransform.GetRotation() + p_Ang);
}

Transform2D operator+(const ke::Angle p_Ang, const Transform2D & p_rTransform)
{
    return Transform2D(p_rTransform.GetTranslation(), p_rTransform.GetRotation() + p_Ang);
}

Transform2D operator+(const Transform2D::Translation2DType & p_rTranslation, const Transform2D & p_rTransform)
{
    return Transform2D(p_rTransform.GetTranslation() + p_rTranslation, p_rTransform.GetRotation());
}

Transform2D operator+(const Transform2D & p_rTransform, const Transform2D::Translation2DType & p_rTranslation)
{
    return Transform2D(p_rTransform.GetTranslation() + p_rTranslation, p_rTransform.GetRotation());
}

Transform2D & operator+=(Transform2D & p_rTransform, const ke::Angle p_Ang)
{
    p_rTransform.SetRotation(p_rTransform.GetRotation() + p_Ang);
    return p_rTransform;
}

Transform2D operator-(const Transform2D & p_rTransform)
{
    return Transform2D(-1.0 * p_rTransform.GetTranslation(), -1.0 * p_rTransform.GetRotation());
}

Transform2D operator-(const Transform2D & p_rLeft, const Transform2D & p_rRight)
{
    return Transform2D(p_rLeft.GetTranslation() - p_rRight.GetTranslation(), p_rLeft.GetRotation() + p_rRight.GetRotation());
}

Transform2D operator-(const Transform2D & p_rTransform, const ke::Angle p_rAng)
{
    return Transform2D(p_rTransform.GetTranslation(), p_rTransform.GetRotation() + p_rAng);
}

Transform2D operator-(const Transform2D & p_rTransform, const Transform2D::Translation2DType & p_rTranslation)
{
    return Transform2D(p_rTransform.GetTranslation() - p_rTranslation, p_rTransform.GetRotation());
}

Transform2D & operator-=(Transform2D & p_rTransform, const Transform2D::Translation2DType & p_rTranslation)
{
    p_rTransform.SetTranslation(p_rTransform.GetTranslation() - p_rTranslation);
    return p_rTransform;
}

Transform2D operator*(const Transform2D & p_rLeft, const Transform2D & p_rRight)
{
    using namespace std;
    using namespace glm;
    const double l_ang_rad(p_rLeft.GetRotation().asRadians());
    const Transform2D::Translation2DType l_complex_rotation(cos(l_ang_rad), sin(l_ang_rad));
    const double r_ang_rad(p_rRight.GetRotation().asRadians());
    const Transform2D::Translation2DType r_complex_rotation(cos(r_ang_rad), sin(r_ang_rad));
    const Transform2D::Translation2DType ret_ang_vec2(l_complex_rotation * r_complex_rotation);
    return Transform2D(p_rLeft.GetTranslation() + p_rRight.GetTranslation(), ke::Angle::radians(atan2(ret_ang_vec2.x, ret_ang_vec2.y)));
}

Transform2D operator*(const Transform2D & p_rTransform, const double p_Scalar)
{
    return Transform2D(p_rTransform.GetTranslation()*p_Scalar, p_rTransform.GetRotation()*p_Scalar);
}

Transform2D operator*(const double p_Scalar, const Transform2D & p_rTransform)
{
    return Transform2D(p_rTransform.GetTranslation()*p_Scalar, p_rTransform.GetRotation()*p_Scalar);
}

Transform2D & operator*=(Transform2D & p_rTransform, const double p_Scalar)
{
    p_rTransform.SetTranslation(p_rTransform.GetTranslation()*p_Scalar);
    p_rTransform.SetRotation(p_rTransform.GetRotation()*p_Scalar);
    return p_rTransform;
}

Transform2D operator/(const Transform2D & p_rTransform, const double p_Scalar)
{
    return Transform2D(p_rTransform.GetTranslation()/p_Scalar, p_rTransform.GetRotation()/p_Scalar);
}

Transform2D & operator/=(Transform2D & p_rTransform, const double p_Scalar)
{
    p_rTransform.SetTranslation(p_rTransform.GetTranslation()/p_Scalar);
    p_rTransform.SetRotation(p_rTransform.GetRotation()/p_Scalar);
    return p_rTransform;
}


} // KE ns