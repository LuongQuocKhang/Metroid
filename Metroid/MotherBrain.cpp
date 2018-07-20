#include "MotherBrain.h"
#include "Game.h"

MotherBrain::MotherBrain(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->enemy_type = MOTHER_BRAIN;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->isActive = true;

	health = HEALTH_MOTHER_BRAIN;

	unbroken = new Sprite(spriteHandler, BOSS_SPRITE_PATH, MOTHER_BRAIN_UNBROKEN_PATH, MOTHER_BRAIN_WIDTH, MOTHER_BRAIN_HEIGHT, MOTHER_BRAIN_SPRITE_COUNT, SPRITE_PER_ROW);
	broken = new Sprite(spriteHandler, BOSS_SPRITE_PATH, MOTHER_BRAIN_BROKEN_PATH, MOTHER_BRAIN_WIDTH, MOTHER_BRAIN_HEIGHT, MOTHER_BRAIN_SPRITE_COUNT, SPRITE_PER_ROW);

	//--TO DO: Khởi tạo collider cho Mother Brain
	collider = new Collider();
	collider->SetCollider(MOTHER_BRAIN_HEIGHT / 2, -MOTHER_BRAIN_WIDTH / 2, -MOTHER_BRAIN_HEIGHT / 2, MOTHER_BRAIN_WIDTH / 2);
}

MotherBrain::~MotherBrain()
{
	delete(unbroken);
	delete(broken);
}

void MotherBrain::Update(float t)
{
	if (!isActive) return;

	// Nếu không nằm trong Camera thì unactive
	if (!IsInCamera())
	{
		isActive = false;
		return;
	}

	pos_x += vx * t;
	pos_y += vy * t;

	if (this->health <= HEALTH_MOTHER_BRAIN - 30)
		state = BROKEN;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case UNBROKEN:
			unbroken->Next();
			break;
		case BROKEN:
			broken->Next();
			break;
		}
		last_time = now;
	}

}

void MotherBrain::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (state)
	{
	case UNBROKEN:
		unbroken->Render(pos_x, pos_y);
		break;
	case BROKEN:
		broken->Render(pos_x, pos_y);
		break;
	}
	spriteHandler->End();
}

void MotherBrain::Destroy()
{
	Enemy::Destroy();
	Game::gameSound->playSound(BACKGROUND_MOTHER_BRAIN_DEATH);
}
