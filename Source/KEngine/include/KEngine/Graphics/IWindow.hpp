#pragma once

#include "Types.hpp"
#include "KEngine/Common/Geometry.hpp"
#include "KEngine/Utility/NonCopyable.hpp"


namespace ke
{

/** 
    \class IRenderSurface
    \brief An abstract base class for implementing render target/surface.

    A render surface has a type which indicates what the surface is (e.g. texture/frame-buffer or window).
*/
class IRenderSurface
    : ke::NonCopyable
{
public:
    enum class Type
    {
        Window,
        Texture,
        Unknown,
    };

protected:
    Type m_SurfaceType = Type::Unknown;

public:
    IRenderSurface(const Type p_Type) : m_SurfaceType(p_Type) {}
    virtual ~IRenderSurface(void) = default;

    /** \return the type of the surface. */
    Type type(void) const { return m_SurfaceType; }

    /** Clear the screen. */
    virtual void clear(const ke::Vec4u & p_rColour4 = ke::Vec4u(0, 0, 0, 255)) = 0;

    /** \return a raw pointer to the internal implementation instance. */
    virtual void * getInternal(void) = 0;
};

/** 
    \class IWindow
    \brief A abstract base class (interface) for implementing a window or display surface.
            This allows specific windowing API detail to be hidden away from user code(both
            engine and projects). E.g. LibraryA offers an A::Window class. A ke::AWindow class
            can be implemented which internally contains and manages an instance of A::AWindow.

    Development note:\n
    In the future where cross-platform and cross-API is required/needed, a separate ISurface or
    IRenderSurface base class can be created where the IWindow class inherits from.
*/
class IWindow
    : public IRenderSurface
{
public:
    IWindow(void) : IRenderSurface(Type::Window) {}
    virtual ~IWindow(void) = 0;

    /** Present the display buffer to screen. */
    virtual void display(void) = 0;    
    /** Close the window. */
    virtual void close(void) = 0;

    /** Set the application window's title. */
    virtual void setWindowTitle(std::string p_Title) = 0;
    
    /** \return true if the window is open. */
    virtual bool isOpen(void) = 0;
};

inline IWindow::~IWindow(void) {}

}