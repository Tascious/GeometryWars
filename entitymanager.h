#pragma once
#include<memory>
#include<map>
#include<vector>
#include"entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string,EntityVec> EntityMap;


class EntityManager
{
    EntityVec m_entities;
    EntityVec m_toAdd;
    EntityMap m_entityMap;

    size_t m_totalEntities ;

    public:
        EntityManager();
        void update();
        std::shared_ptr<Entity> addEntity(const std::string &tag);
        EntityVec &getEntities();
        std::shared_ptr<Entity>& getEntity(const std::string &tag);
        void removeDeadEntities(std::shared_ptr<Entity> &vec);
};