#pragma once
#include <memory>
#include <list>
#include <vector>

namespace ke
{

class Task;
using TaskSPtr     = std::shared_ptr<ke::Task>;
using TaskWPtr     = std::weak_ptr<ke::Task>;
using TaskUPtr     = std::unique_ptr<ke::Task>;

class TaskManager;
using TaskManagerSPtr  = std::shared_ptr<ke::TaskManager>;
using TaskManagerWPtr  = std::weak_ptr<ke::TaskManager>;
using TaskManagerUPtr  = std::unique_ptr<ke::TaskManager>;

using TaskSPList        = std::list<ke::TaskSPtr>;
using TaskSPVector      = std::vector<ke::TaskSPtr>;

} // KE ns
