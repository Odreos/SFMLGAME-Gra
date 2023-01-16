#include "Animation.hpp"

void Animation::SetAmountAnimations(int x)
{
	amountAnimation = x;
	iterate = 0;
}

void Animation::SetTxt(Texture* t, int x)
{
	amountAnimation = x;
	animationTxt = t;
	actualAnimation.setTexture(*t);
	actualAnimation.setTextureRect({ 0,0,(int)(animationTxt->getSize().x / amountAnimation),(int)animationTxt->getSize().y });


	actualAnimation.setOrigin({animationTxt->getSize().x / (float)amountAnimation / 2.f,(float)animationTxt->getSize().y });
}

void Animation::SetSpeed(float x)
{
	speedAnimation = x;
}

void Animation::Play()
{
	play = 1;
}

void Animation::Stop()
{
	play = 0;
	deltaTime = 0;
	iterate = 0;
}

void Animation::SetPos(Vector2f pos)
{
	actualAnimation.setPosition(pos);
}

void Animation::SetAngle(float angle)
{
	actualAnimation.setRotation(angle);
}

void Animation::Update(float dt)
{
	if (play)
	{
		deltaTime += dt;
		if (deltaTime >= speedAnimation)
		{
			int w = iterate * animationTxt->getSize().x / amountAnimation;

			//actualAnimation = Sprite(*animationTxt, IntRect(w, 0, w + animationTxt->getSize().x / amountAnimation, animationTxt->getSize().y));
			
			IntRect x = { w,0,(int)(animationTxt->getSize().x / amountAnimation),(int)animationTxt->getSize().y };

			actualAnimation.setTextureRect(x);

			iterate++;

			if (iterate >= amountAnimation)
			{
				iterate = 0;
			}

			deltaTime -= speedAnimation;
		}
	}
}

void Animation::Draw(RenderWindow& window)
{
	if (play)
		window.draw(actualAnimation);
}
