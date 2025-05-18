#ifndef DANGERZONE_H
#define DANGERZONE_H

#include "Character.h"
#include<vector>

class Character;								// Forward declaration --> avoid circulation

class DangerZone
{
public:
	DangerZone();
	~DangerZone();
	std::vector<std::vector<int>>				getDangerZone();
	void										updateDangerZone(std::vector<std::vector<int>> enemyMoves, std::vector<std::vector<int>> zone);
	void										updateDangerZonePawns(std::vector<std::vector<int>> zone, int i, int j, int player);
	void										updateDangerZoneKing(std::vector<std::vector<int>> zone, int i, int j);
	void										createDangerZone(std::vector<std::vector<Character*>> board, int player);
	bool										noChess(std::vector<int> kingPos);

private:
	
	std::vector<std::vector<int>>				dangerZone;
};

#endif // DANGERZONE_H
