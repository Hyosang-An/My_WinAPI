#pragma once

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END
};

enum class BRUSH_TYPE
{
	RED,
	GREEN,
	BLUE,
	GRAY,

	DELETE_END,

	// HOLLOW와 BLACK은 삭제하면 안됨
	HOLLOW,
	BLACK,

	END
};

enum class LEVEL_TYPE
{
	LOGO_START,
	EDITOR,

	STAGE_01,
	STAGE_02,
	STAGE_03,

	BOSS_01,

	END,
};

enum class PLAYER_STATE
{
	IDLE,
	RUN,
	MOVE,
	DASH,
	ATTACK,
	HIT,
	DEAD,

	END,
};