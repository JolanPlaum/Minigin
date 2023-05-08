#pragma once

namespace dae
{
	enum class EventType
	{
		PLAYER_DIED,

		ENEMY_DIED,
		ENEMY_DIED_FLYING,
		
		SCORE_CHANGED,

		BULLET_FIRED,
		BULLET_MISSED,
		BULLET_HIT,
	};
}

