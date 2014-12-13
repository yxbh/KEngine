#include <KEngine/Common/Angle.hpp>
#include <KEngine/Common/Geometry.hpp>


namespace ke
{

const Angle Angle::Zero(Angle(0.0)); // TODO : add constexpr here

Angle & Angle::normalise(const ke::Angle p_UpperWrapVal, const ke::Angle p_LowerWrapVal)
{
    assert(p_UpperWrapVal > p_LowerWrapVal);
    if (*this > p_UpperWrapVal)
        *this = ke::Angle::degrees(-180.0) - (*this % p_UpperWrapVal);
    else if (*this < p_LowerWrapVal)
        *this = ke::Angle::degrees(180.0) - (*this % p_LowerWrapVal);
    return *this;
}


} // KE ns
