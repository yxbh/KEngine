#pragma once
#include <memory>
#include <list>
#include <vector>

namespace ke
{

class Task;
using TaskSptr     = std::shared_ptr<ke::Task>;
using TaskWptr     = std::weak_ptr<ke::Task>;
using TaskUptr     = std::unique_ptr<ke::Task>;

class TaskManager;
using TaskManagerSptr  = std::shared_ptr<ke::TaskManager>;
using TaskManagerWptr  = std::weak_ptr<ke::TaskManager>;
using TaskManagerUptr  = std::unique_ptr<ke::TaskManager>;

using TaskSPList        = std::list<ke::TaskSptr>;
using TaskSPVector      = std::vector<ke::TaskSptr>;

} // KE ns
