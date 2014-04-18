#include "Hero.h"


Hero::Hero()
{
	hero_position = vector3df(50, 0, 200);
	hero_roat = vector3df(0, 0, 0);
}

void Hero::HeroPosition(float dx, float dy, float dz)
{
	hero_position = vector3df(this->hero_position.X + dx, this->hero_position.Y + dy, this->hero_position.Z + dz);
}

void Hero::Show()
{
	node->setRotation(hero_roat);
	node->setPosition(hero_position);
	node->setVisible(true);
}

void Hero::Move(float dx, float dy, float dz, int textura, vector3df scale)
{
	Hide();
	Create(textura, scale);
	HeroPosition(dx, dy, dz);
	Show();
}

Hero::~Hero()
{
}
