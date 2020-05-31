#pragma once

#include "ternary_logic.cpp"
#include "shuffle_vars.h"

// main for testing
int main()
{
	printf("\nGoing to run:\n");
	ternarylogic::test::tests();
	ternarylogic::swap::test::test_shuffle_variables();
	printf("\nPress RETURN to finish:");
	static_cast<void>(getchar());
	return 0;
}
