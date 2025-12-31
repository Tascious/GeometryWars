#include"game.h"
#include<iostream>
#include<string>

Game::Game(const std::string &config)
{
    init(config);
}

void Game::init(const std::string & path)
{
    m_window.create(sf::VideoMode(1280,720),"Assignment 2");
    m_window.setFramerateLimit(60);
    m_running = true;




    
}

void Game::run()
{
    //impement pause function
    while(m_running)
    {
        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sRender();


        m_currentFrame ++;
    }
}


void Game::spawnPlayer()
{
    auto entity = m_entities.addEntity("player");
    float mx = m_window.getSize().x/2.0f;
    float my = m_window.getSize().y/2.0f;

    entity->cTransform = std::make_shared<CTransform>(Vec2(mx,my),Vec2(1.0f,1.0f),0.0f);
    entity->cShape = std::make_shared<CShape>(32.0f,8,sf::Color(10,10,10),sf::Color(255,0,0),4.0f);
    entity->cInput =std::make_shared<CInput>();

    m_player =entity;
}

void Game :: spawnEnemy()
{
    float ex = rand()%m_window.getSize().x;
    float ey = rand()%m_window.getSize().y; 
    m_lastEnemySpawnTime = m_currentFrame;

    auto e = m_entities.addEntity("enemy");
    e->cInput =std::make_shared<CInput>();
    e->setStatus(true);
    e->cShape =std::make_shared<CShape>(15.0f,3,sf::Color(10,10,10),sf::Color(0,255,0),3.0f);
    e->cTransform =std::make_shared<CTransform>(Vec2(ex,ey),Vec2(),0.1f);
    //e->cLifespan =std::make_shared<CLifespan>(100,100);
    
}
void Game::sMovement()
{

    if(m_player->cInput->up)
    {
            m_player->cTransform->pos -=Vec2(5.0,0)*m_currentFrame;
    }
    if(m_player->cInput->down)
    {
        m_player->cTransform->pos +=Vec2(5.0,0)* m_currentFrame;
    }

}
void Game::spawnBullet(std::shared_ptr<Entity> entity,const Vec2 &mousePos)
{
    auto bullet = m_entities.addEntity("bullet");

    bullet->cTransform = std::make_shared<CTransform>(mousePos,Vec2(0,0),0);
}

void Game::sUserInput()
{


    while(m_window.pollEvent())
    {
        if(==sf::Event::Closed())
        {
            m_running = false;
        }
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Scan))
        {
            switch(sf::Keyboard::Key())
            {
                case sf::Keyboard::Key::W :
                    std::cout<<"W key pressed\n";
                    m_player->cInput->up = true;
                    break; 
                case sf::Keyboard::Key::D :
                        m_player->cInput->down=true;
                        std::cout<<"D key pressed\n";
                        break;
                case sf::Keyboard::Key::Space:
                    std::cout<<"Space tab pressed \n";
                    m_paused=true;

            }
        }
        if(sf::Event::KeyReleased())
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Key::W :
                    std::cout<<"W key Released\n";
                    m_player->cInput->up = false;
                    break;

            }
        }
        if(sf::Event::KeyPressed())
        {
            switch(sf::Mouse::Button())
            {
                case sf::Mouse::isButtonPressed(sf::Mouse::Button::Left):

                spawnBullet(m_player,Vec2(event.mouseButton.x,event.mouseButton.y));
            }
        }
    

    }
}

void Game::sCollision()
{
    for(auto &b: m_entities.getEntity("bullet"))
    {
        for(auto &e: m_entities.getEntity("enemy"))
        {
        if(b==e)
        {
            e->setStatus(false);
            b->setStatus(false);
            break;
        }
        }
    }
    for(auto &p: m_entities.getEntity("player"))
    {
        for(auto &e: m_entities.getEntity("enemy"))
        {
            if(p==e)
            {
                p->setStatus(false);
                break;
            }
        }
    }

}
void Game::sRender(const & m_entities)
{
    for(auto &e : m_entities)
    {
    m_window.display(e);
    }
    m_window.clear();
}