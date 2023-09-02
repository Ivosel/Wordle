#pragma once

namespace WordleConstants {

	enum Difficulty {
		Easy,
		Medium,
		Hard
	};

	constexpr int WindowWidth = 800;
	constexpr int WindowHeight = 600;
	constexpr int DiffButtonW = 300;
	constexpr int DiffButtonH = 50;
	constexpr int GuessLabelsHspacing = 5;
	constexpr int GuessLabelsVspacing = 15;
	constexpr int LabelDimension = 50;
	constexpr int KeyDimension = 40;
	constexpr int DefaultChances = 6;
	constexpr int LastRow = 5;
}