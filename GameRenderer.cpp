#include <iostream>
#include <algorithm>
#include <cmath>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "GameRenderer.h"
#include "ResaurceManager.h"
#include "Object.h"
#include "ObjectManager.h"
#include "TextRenderManager.h"


Object::BrickColor& GameRenderer::operator()(int row, int col)
{
    assert(row >= 0 && row < Input::rows );
    assert(col >= 0 && col < Input::columns);

    return m_bricks[row * Input::columns + col ];
}

GameRenderer::~GameRenderer()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void GameRenderer::setKeys(int key, bool b) { m_keys[key] = b; }


void GameRenderer::initialize()
{
    GLuint VAO, VBO;    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    m_VAO = VAO;
    m_VBO = VBO;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Input::vertices), Input::vertices, GL_STATIC_DRAW);    
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Input::width), 0.0f,
        static_cast<float>(Input::height), -1.0f, 1.0f);
   
    this -> loadStage(Input::stages[2]);
    auto& rm = ResaurceManager::getInstance();
    rm.loadTexture2D("ball", "textures/ball.png");
    rm.loadTexture2D("solidBrick", "textures/greyBrick.jpg");
    rm.loadTexture2D("brick", "textures/square8.png"); 
    rm.loadTexture2D("paddle", "textures/square4.png");
    

    rm.loadVertexShader("main", "shaders/vertex.txt");
    rm.loadFragmentShader("main", "shaders/fragment.txt"); 
    rm.createShaderProgram("main");
    auto& shaderProgram = rm.getShaderProgram("main");
    shaderProgram.addShader(rm.getVertexShader("main"));
    shaderProgram.addShader(rm.getFragmentShader("main"));
    shaderProgram.linkProgram();
    shaderProgram.setUniform("projection", projection);

    //text
    rm.loadVertexShader("text", "shaders/text_vertex.txt");
    rm.loadFragmentShader("text", "shaders/text_fragment.txt");
    rm.createShaderProgram("text");
    auto& textShaderProgram = rm.getShaderProgram("text");
    textShaderProgram.addShader(rm.getVertexShader("text"));
    textShaderProgram.addShader(rm.getFragmentShader("text"));
    textShaderProgram.linkProgram();    
    textShaderProgram.setUniform("projection", projection);
    auto& trm = TextRenderManager::getInstance();
    trm.createFont("text", "fonts/calibri/calibril.ttf", 48);

       
    auto& om = ObjectManager::getInstance();
    om.createObject("ball", glm::vec2(Input::ballRadius * 2), glm::vec2(0), 
        glm::vec2(static_cast<float>(Input::width) / 2, Input::paddleSize.y + Input::ballRadius), Object::grey);
    om.createObject("brick", glm::vec2( Input::brickSize.x, Input::brickSize.y), glm::vec2(0), 
        glm::vec2(Input::brickSize));
    om.createObject("paddle", Input::paddleSize, glm::vec2(0),
        glm::vec2(static_cast<float>(Input::width) / 2, Input::paddleSize.y / 2), Object::grey);
    om.createObject("background", glm::vec2(Input::width, Input::height), glm::vec2(0), glm::vec2(Input::width/2, Input::height/2));    
}

void GameRenderer::update(double dt)
{
    auto& om = ObjectManager::getInstance();
    auto& ball = om.getObject("ball");
    auto& paddle = om.getObject("paddle");   
    
    if (!m_inGame)
    {
        //ball stays on paddle until SPACE is pressed
        ball.setPosition(glm::vec2(paddle.getPosition().x, Input::paddleSize.y + Input::ballRadius));
        ball.setVelocity(paddle.getVelocity());
        
        if (m_keys[GLFW_KEY_SPACE])
        {            
            ball.setVelocity(Input::ballVelocity);            
            m_inGame = true;
        }
    }    

    if (m_inGame)
    {
        if (collision(ball, paddle))            
        {
            
            float offset{ ball.getPosition().x - paddle.getPosition().x };
            ball.setVelocity(glm::vec2(600 * offset / Input::paddleSize.x , ball.getVelocity().y));
        }
    }

    if (m_keys[GLFW_KEY_D])
    {
        paddle.setVelocity(glm::vec2(Input::paddleSpeed, 0));
        paddle.motion(dt);
    }
    else
        paddle.setVelocity(glm::vec2(0));

    if (m_keys[GLFW_KEY_A])
    {
        paddle.setVelocity(glm::vec2(-Input::paddleSpeed, 0));
        
    }
    else
        paddle.setVelocity(glm::vec2(0));

    //ball goes down out of scope
    if (ball.getPosition().y < -Input::ballRadius && !m_stageComplete)
    {
        m_inGame = false;        
       // this -> loadStage(Input::stages[m_stageNumber]);
    }
   
    if (m_stageComplete)
    {            
        if (m_keys[GLFW_KEY_ENTER])
        {
            m_stageNumber += 1;
            m_inGame = false;
            if (m_stageNumber < Input::numberOfStages)
            {            
                this->loadStage(Input::stages[m_stageNumber]);
            }
            else
            {
                m_stageNumber = 0;
                this->loadStage(Input::stages[m_stageNumber]);
            }
        }
    }
    ball.motion(dt);
    paddle.motion(dt);
}

void GameRenderer::render()
{    
    auto& rm = ResaurceManager::getInstance();
    auto& shaderProgram = rm.getShaderProgram("main"); 
    auto& textShaderProgram = rm.getShaderProgram("text");
    
    auto& om = ObjectManager::getInstance();
    auto& ball = om.getObject("ball");
    auto& brick = om.getObject("brick");
    auto& paddle = om.getObject("paddle");    
        
    auto& ballTexture = rm.getTexture("ball");    
    auto& brickTexture = rm.getTexture("brick");
    auto& solidBrickTexture = rm.getTexture("solidBrick");
    auto& paddleTexture = rm.getTexture("paddle");
     
    auto& trm = TextRenderManager::getInstance();
    auto& font = trm.getFont("text");
    glBindVertexArray(m_VAO);    
    
    ball.draw(shaderProgram, ballTexture);
    m_stageComplete = true;

    for (int i{0}; i < Input::rows; ++i)
    {
        for (int j{ 0 }; j < Input::columns; ++j)
        {
            if ((*this)(i, j) != Object::none)
            {
                glm::vec2 brickPosition(Input::brickSize.x / 2 + j * Input::brickSize.x, 
                    Input::height - Input::brickSize.y / 2 - i * Input::brickSize.y);
                brick.setPosition(brickPosition);
                if (collision(ball, brick) && (*this)(i, j) != Object::grey)
                {                          
                    (*this)(i, j) = Object::none;
                    continue;                    
                }
                if ((*this)(i, j) == Object::grey)
                {
                    brick.setColor((*this)(i, j));                    
                    brick.draw(shaderProgram, solidBrickTexture);                   
                }
                else
                {
                    brick.setColor((*this)(i, j));
                    brick.draw(shaderProgram, brickTexture);
                    m_stageComplete = false;
                }
            }
        }
    }     
   
    ball.draw(shaderProgram, ballTexture);
    paddle.draw(shaderProgram, paddleTexture);
    if (!m_inGame)
    {
        font.RenderText(textShaderProgram, 
            "Press A or D to move the paddle ", 25.0f, 225.0f, 0.8f, glm::vec3(0.5, 0.8f, 0.2f));
        font.RenderText(textShaderProgram, 
            "Press SPACE to start the game or ESC to quit", 25.0f, 175.0f, 0.8f, glm::vec3(0.5, 0.8f, 0.2f));
    }

    if (m_stageComplete)
    {
        font.RenderText(textShaderProgram, " CONGRATULATTIONS!!!", 155.0f, 255.0f, 2.0f, glm::vec3(0.8, 0.8f, 0.2f));
        font.RenderText(textShaderProgram, "Press ENTER to start new stage or ESC to quit",
            25.0f, 155.0f, 0.8f, glm::vec3(0.1, 0.8f, 0.2f));
    }
}

bool GameRenderer::collision(Object& ball, Object& brick)
{
    //Collision happen when two objects overlap both vertically and horizontally
    glm::vec2 relativePosition{ brick.getPosition() - ball.getPosition()};
    bool overlapX{ abs(relativePosition.x) < Input::ballRadius  + brick.getSize().x / 2};
    bool overlapY{ abs(relativePosition.y) < Input::ballRadius  + brick.getSize().y / 2};

    //If ball is close to a brick corner it may be not in touch with brick even if there is both horizontal and vertical overlap,
    //To address this issue corner correction is introduced
    bool cornerCorrection{ glm::length(relativePosition) < glm::length(brick.getSize())/2 + Input::ballRadius};
    
    //Horizontal collision happens when ball goes through the bottom or top of a brick, and vertical
    //when it goes through the sides. 
    bool hotizontalCollision{ abs(glm::normalize(relativePosition).y) > glm::normalize(brick.getSize()).y };
   
    if (overlapX && overlapY && cornerCorrection)
    {
        if (hotizontalCollision)
        {          
            int sign = static_cast<int>(relativePosition.y / abs(relativePosition.y)) ;
            
            //Ball position is checked every frame so it might be not the same as collision position, so we need to move our ball
            //back to the place of collision. 
            float posY = brick.getPosition().y - sign * (brick.getSize().y / 2 + Input::ballRadius);
            float posX = ball.getPosition().x - (ball.getVelocity().x / ball.getVelocity().y) * (ball.getPosition().y - posY);
            ball.setPosition(glm::vec2(posX, posY));
            ball.setVelocity(glm::vec2(ball.getVelocity().x, -ball.getVelocity().y));
        }
        else
        {        
            int sign = static_cast<int>(relativePosition.x / abs(relativePosition.x));
            float posX = brick.getPosition().x - sign * (brick.getSize().x / 2 + Input::ballRadius);
            float posY = ball.getPosition().y;
            ball.setPosition(glm::vec2(posX, posY));            
            ball.setVelocity(glm::vec2( -ball.getVelocity().x, ball.getVelocity().y));            
        }
    }


    return overlapX && overlapY && cornerCorrection;
}

void GameRenderer::loadStage(const Input::BrickColor* stage)
{
    Input::BrickColor element{};
    for (int i{ 0 }; i < Input::size; ++i)
    {
        element = stage[i];
        switch (element)
        {
        case Input::BrickColor::n: m_bricks[i] = Object::none;
            break;
        case Input::BrickColor::s: m_bricks[i] = Object::grey;
            break;
        case Input::BrickColor::b: m_bricks[i] = Object::blue;
            break;
        case Input::BrickColor::g: m_bricks[i] = Object::green;
            break;
        case Input::BrickColor::r: m_bricks[i] = Object::red;
            break;
        case Input::BrickColor::y: m_bricks[i] = Object::yellow;
            break;
        default: m_bricks[i] = Object::none;
            break;
        };
    }
}

void GameRenderer::clearResaurces()
{
    ResaurceManager::getInstance().clearCache();
    ObjectManager::getInstance().clearCache();
    TextRenderManager::getInstance().clearCache();
}