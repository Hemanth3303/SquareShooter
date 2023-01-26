#pragma once

#include "pch.hpp"

enum class States {
	Menu = 0,
	Playing,
	Pause,
	GameOver,
};

static std::ostream& operator<<(std::ostream& stream, States state) {
	switch (state) {
		case States::Menu:
			stream << "Menu";
			break;
		case States::Playing:
			stream << "Playing";
			break;
		case States::Pause:
			stream << "Pause";
			break;
		case States::GameOver:
			stream << "GameOver";
			break;
	}
	return stream;
}