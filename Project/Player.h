#pragma once
#include "DEFAULT.h"

#define JumpMaxHeight 50;

using namespace me::math;

class Player
{
public:
	Player();
	~Player();

	void AddPos(Vector2 _Pos) { Pos += _Pos; }
	Vector2 GetPos() { return Pos; }

private:
	Vector2 Pos;
};

