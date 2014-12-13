#pragma once

#include "IWindow.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

namespace ke
{

/** 
    \class SfmlWindow
    \brief A ke::IWindow implementation which uses SFML's windowing class.
*/
class SfmlWindow final
    : public IWindow
{
    sf::RenderWindow m_Window;

public:
    virtual ~SfmlWindow(void) = default;

    virtual void display(void) final;
    virtual void clear(const ke::Vec4u & p_rColour4 = ke::Vec4u(0, 0, 0, 255)) final;
    virtual void close(void) final;

    virtual bool isOpen(void) final;

    virtual void setWindowTitle(std::string p_Title) final;
    
    virtual void * getInternal(void) final;

    bool setActive(bool p_Active = true);
};

}