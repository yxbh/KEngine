#pragma once
#include "Types.hpp"
#include "../Common/Queues.hpp"

namespace ke
{

using EventQueue = ke::ThreadSafeQueue<EventSptr>;

} // KE ns
