#pragma once
#include <memory>
#include <list>

namespace ke
{

////
class KELogic;
using LogicSPtr    = std::shared_ptr<KELogic>;
using LogicWPtr    = std::weak_ptr<KELogic>;
using LogicUPtr    = std::unique_ptr<KELogic>;

////
class KEApp;
using AppUPtr      = std::unique_ptr<KEApp>;
using AppSPtr      = std::shared_ptr<KEApp>;
using AppWPtr      = std::weak_ptr<KEApp>;

////
class IView;
using ViewSPtr     = std::shared_ptr<IView>;
using ViewWPtr     = std::weak_ptr<IView>;
using ViewUPtr     = std::unique_ptr<IView>;

using ViewSPList    = std::list<ViewSPtr>;

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