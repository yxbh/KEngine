#pragma once
#include "EntityComponentID.hpp"
#include "EntityID.hpp"
#include <memory>
#include <vector>
#include <map>

namespace ke
{
class Entity;
using EntitySptr       = std::shared_ptr<ke::Entity>;
using EntityWptr       = std::weak_ptr<ke::Entity>;
using EntityUptr       = std::unique_ptr<ke::Entity>;
using EntityMap         = std::map<ke::EntityID, ke::Entity>;
using EntitySPMap       = std::map<ke::EntityID, ke::EntitySptr>;

class IEntityManager;
using EntityManagerSptr = std::shared_ptr<ke::IEntityManager>;
using EntityManagerWptr = std::weak_ptr<ke::IEntityManager>;
using EntityManagerUptr = std::unique_ptr<ke::IEntityManager>;

using EntityComponentType = std::uint64_t;

class IEntityComponent;
using EntityComponentSptr  = std::shared_ptr<ke::IEntityComponent>;
using EntityComponentWptr  = std::weak_ptr<ke::IEntityComponent>;
using EntityComponentUptr  = std::unique_ptr<ke::IEntityComponent>;

using EntityComponentSPList = std::vector<ke::EntityComponentSptr>;
using EntityComponentSPMap  = std::map<ke::EntityComponentType, ke::EntityComponentSptr>;

} // KE ns
