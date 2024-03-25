#include "Planete.h"
#include "Systeme.h"
#include "utils.h"
#include <array>
#include <iostream>


int main ()
{
	Planete <long double, 2> terre (5.972168e24, 1.9885e30, {0.0167086, 149598023, 0, 0, 0, 0});
	Planete <long double, 2> soleil (1.9885e30, {terre});

	Systeme <long double, 2, 2> s {soleil, terre};
	s.simulation <5> (1e-15);

	return 0;
}
