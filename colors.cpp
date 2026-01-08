#include "Colors.h"
#include <vector>

const Color pink = { 210, 132, 213, 255 };
const Color darkGrey = { 26, 31, 40, 255 };
const Color green = { 47, 230, 23, 255 };
const Color red = { 232, 18, 18, 255 };
const Color orange = { 226, 116, 17, 255 };
const Color yellow = { 237, 234, 4, 255 };
const Color purple = { 166, 0, 247, 255 };
const Color blue = { 13, 64, 216, 255 };


std::vector<Color> GetCellColours()
{

	return { darkGrey, pink, green, red,orange, yellow, purple, blue };
}