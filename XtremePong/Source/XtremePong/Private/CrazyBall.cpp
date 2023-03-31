#include "CrazyBall.h"

FVector CrazyBall::doReverseBall(FVector curr)
{
	return curr * -1;
}

FVector CrazyBall::slowBall(FVector curr, float factor)
{
	if (factor < 1 && factor > 0)
	{
		return curr * factor;
	}
	return curr;
}
