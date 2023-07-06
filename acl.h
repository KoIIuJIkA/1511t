#pragma once

#include <iostream>
#include <string>
#include <functional>

namespace access {
    template<class Entity, class Resource, class AccessMode = bool>
    class ACL {
    public:
        using EntityId = std::size_t;

        void AddEntity(EntityId const& e, Resource const& r, AccessMode m) noexcept {
            try {
                GetAccessMode(e, r);
            } catch (...) {
                entities[e][r] = m;
            }
        }

        void DelEntity(EntityId const& e) noexcept {
            entities.erase(e);
        }

        AccessMode GetAccessMode(EntityId const& e, Resource const& r) const {
        auto entityIt = entities.find(e);
            if (entityIt != entities.end()) {
                auto resourceIt = entityIt->second.find(r);
                if (resourceIt != entityIt->second.end()) {
                    return resourceIt->second;
                } else {
                    throw std::out_of_range("no such resourse in entities");
                }
            } else {
                throw std::out_of_range("no such entity");
            }
            return AccessMode();    
        }

        void SetAccessMode(EntityId const& e, Resource const& r, AccessMode m) noexcept {
            try {
                (entities.at(e)).at(r) = m;
            } catch (const std::out_of_range& msg) {
                std::cerr << msg.what() << std::endl;
            }
        }

        EntityId getId(Entity const e) const noexcept {
            std::hash<Entity> hasher;
            return hasher(e);
        } 

        void ShowEntities() const noexcept {
            for (auto& entityId : entities) {
                for (auto& resourse : entityId.second) {
                    std::cout << "access-list -> "<< entityId.first << " -> " << resourse.first \
                        << " -> " << resourse.second << std::endl; 
                }
            }
        }

    private:
        std::unordered_map<EntityId, std::unordered_map<Resource, AccessMode>> entities;
    }; 
} /// namespace access.
