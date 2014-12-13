#pragma once
#include <memory>
#include <list>

namespace ke
{

////
class Logic;
using LogicSptr    = std::shared_ptr<Logic>;
using LogicWptr    = std::weak_ptr<Logic>;
using LogicUptr    = std::unique_ptr<Logic>;

////
class App;
using AppUptr      = std::unique_ptr<App>;
using AppSptr      = std::shared_ptr<App>;
using AppWptr      = std::weak_ptr<App>;

////
class IView;
using ViewSptr     = std::shared_ptr<IView>;
using ViewWptr     = std::weak_ptr<IView>;
using ViewUptr     = std::unique_ptr<IView>;

using ViewSPList    = std::list<ViewSptr>;

////
using ViewID        = unsigned;
const ViewID InvalidViewID = 0x0;


/** \class ViewType
    \brief View layer types.
*/
enum class ViewType
{
    Human,      // local player.
    AI,         //
    Remote,     // controled by a human over a network.
    Recorder,   // a recording service for replay purposes.
    Other,      //
};

} // KE ms