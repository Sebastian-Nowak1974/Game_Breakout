#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameInputData.h"

class GameRenderer
{
public:
	~GameRenderer();

	//Overloading bracket operator to transform array of bricks into two dimensional grid
	Object::BrickColor& operator()(int row, int col);
	void setKeys(int key, bool b);
	//Function loading data to initialize game, shaders, textures, objects...
	void initialize();
	//Updates variables for each frame (objects positions, velocities, collisions and so on)
	void update(double dt);	
	void render();
	//Loading stage to the game
	void loadStage(const Input::BrickColor* level);
	//Managing ball collisions 
	static bool collision(Object& ball, Object& brick);
	//Cleanup function
	void clearResaurces();

public:
	GLuint m_VAO; 
	GLuint m_VBO;	
	bool m_inGame{ false }; //Turns to true when the ball is launched from the paddle
	bool m_stageComplete{ false }; //Tells if a stage is completed
	bool m_keys[1024]; //Set by key call back function. True when a key is pressed and false when released
	Object::BrickColor m_bricks[Input::size]{}; //Stage arrangement, array index defines brick location, and 
	                                            //value defines brick type and color
	unsigned int m_stageNumber{ 0 }; //Stage number
};