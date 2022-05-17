#pragma once

template <typename firstType, typename secondType>

class Pair {
	firstType first;
	secondType second;

public:
	Pair() {
	}

	Pair(firstType _first, secondType _second) {
		first = _first;
		second = _second;
	}

	firstType getFirst() {
		return first;
	}

	secondType getSecond() {
		return second;
	}
};