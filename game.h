#pragma once
#include "entity.h"
#include"entitymanager.h"
#include<SFML/Graphics.hpp>


struct playerConfig{int shapeR,cR,fillR,fillG,fillB,outR,outG,outB,outT,vel;float s;};
struct enemyConfig{int shapeR,circleR,outG,outB,outT,vmin,vmax,l,SI;float sMIN,sMAX;};
struct bulletConfig{int sR,cR,fillR,fillG,fillB,outR,outG,outB,outT,vel,l;float s;};
class Game
{
    sf::RenderWindow m_window;
    EntityManager  m_entities;
    sf::Font         m_font;
    sf::Text         m_text;
    playerConfig     m_playerConfig;
    enemyConfig      m_enemyConfig;
    bulletConfig     m_bulletConfig;
    int              m_score;
    int              m_currentFrame = 0;
    int              m_lastEnemySpawnTime = 0;
    bool             m_paused       = false;
    bool             m_running       = false;

    std::shared_ptr<Entity>  m_player;
    
    void  init(const std::string &config);
    void setPaused(bool paused);

    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender(const & m_entities);
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity,const Vec2 &mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

    public:
        Game(const std::string &config);
        void run();

};
