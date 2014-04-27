#include <iostream>
#include "../../include/engine_common.hpp"
#include "../../include/App/KEApp.hpp"
#include "../../include/Event/EventManager.hpp"
#include "../../include/Event/IEvent.hpp"
#include "../../include/Utility/StopWatch.hpp"
#include "../../include/Utility/Angle.hpp"
#include "../../../ProjectK/src/App/ProjKApp.hpp"
#include "../../include/App/App.hpp"

static void end(KE::Event_SharedPtr p_spEvent)
{
    KE::Debug::Print("HELLO");
    static KE::EventType type;
    type = p_spEvent->GetType();
    static unsigned bob { 0 };
    ++bob;
}

class foo
{
public:
    void end(KE::Event_SharedPtr p_spEvent)
    {
        static KE::EventType type;
        type = p_spEvent->GetType();
        static unsigned bob { 0 };
        ++bob;
    }
};

using EventDelegateFuncType = void(*)(KE::Event_SharedPtr);

int main(void)
{
    KE::Debug::Print("Hello World!");

    KE::App::Set(new PK::ProjKApp);
    if (!KE::App::Get().Init())
        assert(false);


    /* test EventManager. */
    bool keep_going { true };
    auto func = [&](KE::Event_SharedPtr p_spEvent)
    {
        keep_going = false;
        return;
    };
    foo foo_obj;
    //KE::EventManager::AddListener(KE::TestEvent::EventType, func, KE::EventManager::GenNewHandle());
    KE::EventManager::AddListener(KE::TestEvent::EventType, &end, KE::EventManager::GenNewHandle());
    KE::EventManager::AddListener(KE::TestEvent::EventType, &foo::end, &foo_obj, KE::EventManager::GenNewHandle());
    /* /test EventManager. */

    /* test angle. */
    KE::Angle ang;
    /* /test angle. */

    KE::StopWatch watch;
    watch.Restart();
    while (keep_going)
    {
        watch.Restart();
        KE::Time elapsed(watch.GetElapsed());
        KE::App::Get().UpdateApp(elapsed);


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            break;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            ang += KE::Angle::Degrees(0.2);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
            ang -= KE::Angle::Degrees(0.2);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            KE::EventManager::QueueEvent(std::make_shared<KE::TestEvent>());


        static KE::Time ang_time; ang_time += elapsed;
        const KE::Time ang_time_c(KE::Time::Milliseconds(200));
        if (ang_time > ang_time_c)
        {
            KE::Debug::Print("Angle (deg) = " + std::to_string(ang.Normalise().AsDegrees()));
            ang_time -= ang_time_c;
        }

    }

    KE::Debug::Print("pausing");
    KE::Debug::Pause();
    KE::App::Free();
}
