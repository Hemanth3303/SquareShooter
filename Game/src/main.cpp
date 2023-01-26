#include "pch.hpp"

#include "Game.hpp"

int main(int argc, char** argv) {

	Game game(960, 540, "TopDownShooter");
	game.run();

	return 0;
}