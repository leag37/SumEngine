// Constructor
SUMINLINE Vertex::Vertex()
{ }

// Constructor
SUMINLINE Vertex::Vertex(const Float3& p)//, const Float4& c)
	: _position(p)//, color(c)//, _normal(n), _tangentU(t), _texC(uv)
{ }

// Constructor
SUMINLINE Vertex::Vertex(
	SFLOAT px, SFLOAT py, SFLOAT pz)
	:	_position(px, py, pz)
{ }

SUMINLINE const Float3& Vertex::position()
{
	return _position;
}
//
//SUMINLINE const Float4& Vertex::color()
//{
//	return _color;
//}

//SUMINLINE const Float3& Vertex::normal()
//{
//	return _normal;
//}
//
//SUMINLINE const Float3& Vertex::tangentU()
//{
//	return _tangentU;
//}
//
//SUMINLINE const Float2& Vertex::texC()
//{
//	return _texC;
//}

