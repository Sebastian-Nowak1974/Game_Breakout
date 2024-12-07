#pragma once
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"

//All game parameters are defined in this header file and they can be controled at this point
namespace Input
{
	//Enum defined to simplify building stages
	enum BrickColor
	{
		n, //none
		s, //solid brick, grey color
		b, //blue
		g, //green
		r, //red
		y //yellow
	};

	//Quad vertices for game objects
	inline constexpr float vertices[] = {
		// pos         // tex
	   -0.5f,  0.5f,   0.0f, 1.0f,
		0.5f, -0.5f,   1.0f, 0.0f,
	   -0.5f, -0.5f,   0.0f, 0.0f,

	   -0.5f,  0.5f,   0.0f, 1.0f,
		0.5f,  0.5f,   1.0f, 1.0f,
		0.5f, -0.5f,   1.0f, 0.0f
	};


	//Brick colors defined
	inline const glm::vec3 blue(0.3f, 0.3f, 0.8f);
	inline const glm::vec3 green(0.2f, 0.6f, 0.3f);
	inline const glm::vec3 red(0.6f, 0.1f, 0.2f);
	inline const glm::vec3 yellow(0.8f, 0.7f, 0.1f);
	inline const glm::vec3 grey(0.5f, 0.5f, 0.5f);

	//Screen size 
	inline constexpr unsigned int width{ 1200 };
	inline constexpr unsigned int height{ 900 };

	//Objects
	inline constexpr float ballRadius{ 17.0f };
	inline const glm::vec2 ballVelocity(100.0f, 700.0f);
	
	inline const glm::vec2 paddleSize(200.0f, 25.0f);
	inline constexpr float paddleSpeed{ 600.0f };	
	
	inline constexpr unsigned int rows{ 10 };
	inline constexpr unsigned int columns{ 16 };
	inline const glm::vec2 brickSize(static_cast<float>(width/columns), static_cast<float>(height / (2 * rows)));
	
	//Bricks arrangement as they will be rendered on the screen
	inline constexpr unsigned int  size{ rows * columns };
	inline constexpr BrickColor stage1[size]
	{
		g, g, n, n, n, r, r, n, n, r, r, n, n, n, g, g,
		g, n, n, s, r, y, y, r, r, y, y, r, s, n, n, g,		
	    n, n, s, r, y, b, b, y, y, b, b, y, r, s, n, n,
	    n, n, r, y, b, b, n, n, n, n, b, b, y, r, n, n,
	    n, n, r, r, y, b, b, n, n, b, b, y, r, r, n, n,
	    n, n, s, r, r, y, b, b, b, b, y, r, r, s, n, n,
		n, n, n, n, s, r, y, y, y, y, r, s, n, n, n, n,
		n, n, n, n, n, n, r, r, r, r, n, n, n, n, n, n,
		g, g, n, n, n, n, n, r, r, n, n, n, n, n, g, g
	};

	inline constexpr BrickColor stage2[size]
	{ 
		y, y, y, y, y, y, n, n, n, n, g, g, g, g, g, g,
		y, y, n, n, y, y, n, n, n, n, g, g, n, n, g, g,
		y, y, n, n, y, y, n, n, n, n, g, g, n, n, g, g,
		y, y, y, y, y, y, n, n, n, n, g, g, g, g, g, g,
		n, n, r, r, n, n, n, g, y, n, n, n, b, b, n, n,
		n, n, r, r, n, n, s, n, n, s, n, n, b, b, n, n,
		n, n, r, r, n, n, g, g, y, y, n, b, b, b, b, n,
		r, r, s, s, r, r, n, n, n, n, b, b, s, s, b, b	
	};

	inline constexpr BrickColor stage3[size]
	{
		g, g, g, g, n, r, n, b, b, b, n, r, g, g, g, g, 
		g, g, y, n, n, r, r, n, b, n, r, r, n, n, g, g,	 
		g, y, n, n, r, r, r, r, n, r, r, r, r, n, y, g,
		g, y, b, n, r, n, b, r, n, r, b, n, r, n, y, y,
		n, n, n, n, r, b, s, b, n, b, s, b, r, n, n, n,
		n, n, n, n, r, n, b, n, r, n, b, n, r, n, n, n,
		n, n, n, n, n, n, n, r, s, r, n, n, n, n, n, n,
		n, n, n, n, n, r, r, s, n, s, r, r, n, n, n, n,
		n, n, n, n, n, r, r, n, n, n, r, r, n, n, n, n,
		s, s, b, n, b, b, n, r, r, r, n, b, b, n, s, s
	};
	
	inline constexpr unsigned int numberOfStages{ 3 };
	const inline constexpr BrickColor* stages[numberOfStages]{ stage1, stage2, stage3};
};

