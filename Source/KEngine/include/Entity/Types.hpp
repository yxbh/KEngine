#pragma once
#include "EntityComponentID.hpp"
#include "EntityID.hpp"
#include <memory>
#include <vector>
#include <map>

namespace ke
{
class Entity;
using EntitySPtr       = std::shared_ptr<ke::Entity>;
using EntityWPtr       = std::weak_ptr<ke::Entity>;
using EntityUPtr       = std::unique_ptr<ke::Entity>;
using EntityMap         = std::map<ke::EntityID, ke::Entity>;
using EntitySPMap       = std::map<ke::EntityID, ke::EntitySPtr>;

class IEntityManager;
using EntityManagerSPtr = std::shared_ptr<ke::IEntityManager>;
using EntityManagerWPtr = std::weak_ptr<ke::IEntityManager>;
using EntityManagerUPtr = std::unique_ptr<ke::IEntityManager>;

using EntityComponentType = std::uint64_t;

class IEntityComponent;
using EntityComponentSPtr  = std::shared_ptr<ke::IEntityComponent>;
using EntityComponentWPtr  = std::weak_ptr<ke::IEntityComponent>;
using EntityComponentUPtr  = std::unique_ptr<ke::IEntityComponent>;

using EntityComponentSPList = std::vector<ke::EntityComponentSPtr>;
using EntityComponentSPMap  = std::map<ke::EntityComponentType, ke::EntityComponentSPtr>;

} // KE ns
