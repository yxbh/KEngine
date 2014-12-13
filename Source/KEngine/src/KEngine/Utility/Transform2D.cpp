#include <KEngine/Utility/Transform2D.hpp>

namespace ke
{

Transform2D::Transform2D(const Transform2D::Translation2DType p_Translation, const ke::Angle p_Ang)
    : m_Translation(p_Translation), m_Rotation(p_Ang)
{}

Transform2D::Transform2D(const double p_TransX, const double p_TransY, const ke::Angle p_Ang)
    : Transform2D(Translation2DType(p_TransX, p_TransY), p_Ang)
{}

Transform2D::Translation2DType Transform2D::getTranslation(void) const
{
    return m_Translation;
}

ke::Angle Transform2D::getRotation(void) const
{
    return m_Rotation;
}

Transform2D & Transform2D::setTranslation(const double p_TransX, const double p_TransY)
{
    m_Translation.x = p_TransX; m_Translation.y = p_TransY;
    return *this;
}

Transform2D & Transform2D::setTranslation(const Translation2DType p_Translation)
{
    m_Translation = p_Translation;
    return *this;
}

Transform2D & Transform2D::setTranslation(const Transform2D & p_rTransform2D)
{
    m_Translation = p_rTransform2D.getTranslation();
    return *this;
}

Transform2D & Transform2D::setTranslationX(const Translation1DType p_NewX)
{
    m_Translation.x = p_NewX;
    return *this;
}

Transform2D & Transform2D::setTranslationY(const Translation1DType p_NewY)
{
    m_Translation.y = p_NewY;
    return *this;
}

Transform2D & Transform2D::setRotation(const ke::Angle p_Ang)
{
    m_Rotation = p_Ang;
    return *this;
}

Transform2D & Transform2D::setRotation(const Transform2D & p_rTransform2D)
{
    m_Rotation = p_rTransform2D.getRotation();
    return *this;
}

Transform2D operator+(const Transform2D & p_rLeft, const Transform2D & p_rRight)
{
    return Transform2D(p_rLeft.getTranslation() + p_rRight.getTranslation(), p_rLeft.getRotation() + p_rRight.getRotation());
}

Transform2D operator+(const Transform2D & p_rTransform, const ke::Angle p_Ang)
{
    return Transform2D(p_rTransform.getTranslation(), p_rTransform.getRotation() + p_Ang);
}

Transform2D operator+(const ke::Angle p_Ang, const Transform2D & p_rTransform)
{
    return Transform2D(p_rTransform.getTranslation(), p_rTransform.getRotation() + p_Ang);
}

Transform2D operator+(const Transform2D::Translation2DType & p_rTranslation, const Transform2D & p_rTransform)
{
    return Transform2D(p_rTransform.getTranslation() + p_rTranslation, p_rTransform.getRotation());
}

Transform2D operator+(const Transform2D & p_rTransform, const Transform2D::Translation2DType & p_rTranslation)
{
    return Transform2D(p_rTransform.getTranslation() + p_rTranslation, p_rTransform.getRotation());
}

Transform2D & operator+=(Transform2D & p_rTransform, const ke::Angle p_Ang)
{
    p_rTransform.setRotation(p_rTransform.getRotation() + p_Ang);
    return p_rTransform;
}

Transform2D operator-(const Transform2D & p_rTransform)
{
    return Transform2D(-1.0 * p_rTransform.getTranslation(), -1.0 * p_rTransform.getRotation());
}

Transform2D operator-(const Transform2D & p_rLeft, const Transform2D & p_rRight)
{
    return Transform2D(p_rLeft.getTranslation() - p_rRight.getTranslation(), p_rLeft.getRotation() + p_rRight.getRotation());
}

Transform2D operator-(const Transform2D & p_rTransform, const ke::Angle p_rAng)
{
    return Transform2D(p_rTransform.getTranslation(), p_rTransform.getRotation() + p_rAng);
}

Transform2D operator-(const Transform2D & p_rTransform, const Transform2D::Translation2DType & p_rTranslation)
{
    return Transform2D(p_rTransform.getTranslation() - p_rTranslation, p_rTransform.getRotation());
}

Transform2D & operator-=(Transform2D & p_rTransform, const Transform2D::Translation2DType & p_rTranslation)
{
    p_rTransform.setTranslation(p_rTransform.getTranslation() - p_rTranslation);
    return p_rTransform;
}

Transform2D operator*(const Transform2D & p_rLeft, const Transform2D & p_rRight)
{
    using namespace std;
    using namespace glm;
    const double l_ang_rad(p_rLeft.getRotation().asRadians());
    const Transform2D::Translation2DType l_complex_rotation(cos(l_ang_rad), sin(l_ang_rad));
    const double r_ang_rad(p_rRight.getRotation().asRadians());
    const Transform2D::Translation2DType r_complex_rotation(cos(r_ang_rad), sin(r_ang_rad));
    const Transform2D::Translation2DType ret_ang_vec2(l_complex_rotation * r_complex_rotation);
    return Transform2D(p_rLeft.getTranslation() + p_rRight.getTranslation(), ke::Angle::radians(atan2(ret_ang_vec2.x, ret_ang_vec2.y)));
}

Transform2D operator*(const Transform2D & p_rTransform, const double p_Scalar)
{
    return Transform2D(p_rTransform.getTranslation()*p_Scalar, p_rTransform.getRotation()*p_Scalar);
}

Transform2D operator*(const double p_Scalar, const Transform2D & p_rTransform)
{
    return Transform2D(p_rTransform.getTranslation()*p_Scalar, p_rTransform.getRotation()*p_Scalar);
}

Transform2D & operator*=(Transform2D & p_rTransform, const double p_Scalar)
{
    p_rTransform.setTranslation(p_rTransform.getTranslation()*p_Scalar);
    p_rTransform.setRotation(p_rTransform.getRotation()*p_Scalar);
    return p_rTransform;
}

Transform2D operator/(const Transform2D & p_rTransform, const double p_Scalar)
{
    return Transform2D(p_rTransform.getTranslation()/p_Scalar, p_rTransform.getRotation()/p_Scalar);
}

Transform2D & operator/=(Transform2D & p_rTransform, const double p_Scalar)
{
    p_rTransform.setTranslation(p_rTransform.getTranslation()/p_Scalar);
    p_rTransform.setRotation(p_rTransform.getRotation()/p_Scalar);
    return p_rTransform;
}


} // KE ns