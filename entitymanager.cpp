#include "entitymanager.h"
#include"entity.h"

EntityManager::EntityManager():
m_toAdd(),m_entities(),m_entityMap(),m_totalEntities(0)
{
}

void EntityManager::update()
{
    for(auto & e : m_toAdd)
    {
            m_entities.push_back(e); 
            m_entityMap[e->tag()].push_back(e);
    }
            
    for(auto &v:m_entities)
    {
        if(!v->isActive())
        {
            removeDeadEntities(v);
        }
    }


    m_toAdd.clear();
}
void EntityManager::removeDeadEntities(std::shared_ptr<Entity> &vec)
{

}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

    m_toAdd.push_back(entity);
    return entity;
}
EntityVec& EntityManager:: getEntities()
{
    return  m_entities;
}
/*std::shared_ptr<Entity>& EntityManager:: getEntity(const std::string &tag)
{
    for(auto &e:m_entities)
    {
        if(tag.compare(e->m_tag))
        {
            return e;
        }
    }
}*/