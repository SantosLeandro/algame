#include "game.hpp"
#include "game/levelmanager.hpp"

Game::Game()
{
}

Game::~Game()
{
    //m_textureManager.release();
}

void Game::initialize()
{
    //game initialization code here
    printf("Game initialized successfully\n");
    m_graphics.setVirtualResolution(426,240);
   
    m_textureManager.load("texture//samus.png");
    m_textureManager.load("texture//devil.png");
    m_textureManager.load("texture//tileset_1616.png");
    m_textureManager.load("texture//tileset.png");

    std::cout << "Textures loaded" << std::endl;
    player = Player(Vector2(100.0f, 100.0f), m_textureManager.get("texture//samus.png"));
    dialogBox = new DialogBox(
        Vector2(0.0f, 0.0f), 
        Vector2(426, 20.0f),
        "Items: 0   Health: 100%   Bullets: 50",
        m_graphics, 
        Font{Color{1.0f, 1.0f, 1.0f, 1.0f}, 16,m_graphics.getFont()}
    );

   
    dialogBox->setBackgroundColor(Color{0.0f, 0.0f, 0.0f, 1.0f});

    guiCamera = Camera(nullptr, 426, 240);
    
    std::vector<std::vector<int>> tiles = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 3, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 3, 2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 3, 2, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
    };

    std::cout << "Tile data created" << std::endl;

    // Texture* tileset = new Texture();
    // tileset->loadFromFile("texture//tileset.png");
    // tileMap = new Tilemap(
    //     tiles,
    //     tileset,
    //     16,
    //     16
    // );
    GameObjectFactory factory;

    
    
   
    // LevelManager::getInstance().loadLevel("level//room_01.json",m_graphics, m_textureManager, factory);
    // LevelManager::getInstance().loadLevel("level//room_02.json",m_graphics, m_textureManager, factory);
    //LevelManager::getInstance().loadLevel("level//room_02.json",m_graphics, m_textureManager, factory);
    //LevelManager::getInstance().getCurrentLevel()->m_player = &player;
    //level = m_mapLoader.load("level//demolevel.json",m_graphics, m_textureManager, factory);

    //level = new Level(factory.create("player", Vector2(100,100),m_textureManager), tileMap);
    //level->initialize(m_graphics);
    // level->m_camera.setMaxWidth(tiles[0].size()*16);
    // level->m_camera.setMaxHeight(tiles.size()*16);

    

    // level->addGameObject(new Enemy(Vector2(50,150), &m_texture));
    // level->addGameObject(new Enemy(Vector2(250,50), &m_texture));
    // level->addGameObject(factory.create("enemy1", Vector2(50,150),m_textureManager));
    // level->addGameObject(factory.create("enemy1", Vector2(250,50),m_textureManager));

    text = "Hello, ALGame!";

    std::cout << "Game objects created" << std::endl;

    world = new World();
    world->loadRoomFromFile("world//world01.json",&m_textureManager);
    

    std::cout << "World loaded" << std::endl;

   
    world->setCurrentRoom("Room_3");
    world->initialize(m_graphics);
    // level->getCamera().setSmooth(0.05f);
    // level->getCamera().moveTo(Vector2(500,500));
}

void Game::update()
{
    world->update();
    //LevelManager::getInstance().getCurrentLevel()->update();
    // level->update();
    // player.update();
    // //tileMap->checkCollision(player);
    // tileMap->processCollision(player);
    
    // player.setPosition(Vector2(
    //     player.getPosition().x + player.getVelocity().x,
    //     player.getPosition().y + player.getVelocity().y
    // ));
    
    //game logic update code here
}

void Game::render()
{
    // al_identity_transform(&transform);
    // al_translate_transform(&transform, player.getPosition().x * -1 + (340 / 2), 0);
    // al_use_transform(&transform);
    //game rendering code here
    m_graphics.clear();
    world->render(m_graphics);
    //LevelManager::getInstance().getCurrentLevel()->render(m_graphics);
    // level->render(m_graphics);
    // tileMap->render(m_graphics,0,0);
    // player.render(m_graphics);
    // //m_graphics.drawRectangle(playerPosition.x, playerPosition.y, playerPosition.x+200, playerPosition.y+200);
    // //dialogBox->render(m_graphics);
    guiCamera.update();
    dialogBox->render(m_graphics);
    //m_graphics.drawText(text.c_str(), 100, 100);
    m_graphics.present();
}
