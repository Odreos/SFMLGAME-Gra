#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Animation
{
public:
	Sprite actualAnimation;
	Texture* animationTxt;
	float speedAnimation;
	float deltaTime;
	int amountAnimation;
	int iterate;
	bool play;

	void SetAmountAnimations(int x);
	void SetTxt(Texture* t, int x);
	void SetSpeed(float x);
	void Play();
	void Stop();
	void SetPos(Vector2f pos);
	void SetAngle(float angle);
	void Update(float dt);
	void Draw(RenderWindow& window);
};

