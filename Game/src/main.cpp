#include "pch.hpp"

#include "Game.hpp"

int main(int argc, char** argv) {

	Game game(1280, 720, "Square-Shooter");
	game.run();

	return 0;
}