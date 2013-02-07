//*************************************************************************************************
// Title: SumString.inl
// Author: Gael Huber
// Description: Defines various methods for creating strings.
//*************************************************************************************************
// TEMP INCLUDE
#include <string>

// Convert a string to an int
SUMINLINE SINT String::toInt() const
{
	return std::stoi(s);
}

SUMINLINE SINT String::toInt()
{
	return std::stoi(s);
}

// Convert a string to an unsigned int
SUMINLINE SUINT String::toUInt() const
{
	return std::stoul(s);
}

SUMINLINE SUINT String::toUInt()
{
	return std::stoul(s);
}

// Convert a string to a floating point
SUMINLINE SFLOAT String::toFloat() const
{
	return std::stof(s);
}

SUMINLINE SFLOAT String::toFloat()
{
	return std::stof(s);
}

// Convert a string to a double
SUMINLINE SDOUBLE String::toDouble() const
{
	return std::stod(s);
}

SUMINLINE SDOUBLE String::toDouble()
{
	return std::stod(s);
}
