// Constructor
SUMINLINE Vertex::Vertex()
{ }

// Constructor
SUMINLINE Vertex::Vertex(const Float3& p, const Float3& n)
	: _position(p), _normal(n)//, _tangentU(t), _texC(uv)
{ }

// Constructor
SUMINLINE Vertex::Vertex(
	SFLOAT px, SFLOAT py, SFLOAT pz,
	SFLOAT nx, SFLOAT ny, SFLOAT nz)
	:	_position(px, py, pz), _normal(nx, ny, nz)
{ }

SUMINLINE const Float3& Vertex::position()
{
	return _position;
}

SUMINLINE const Float3& Vertex::normal()
{
	return _normal;
}

//SUMINLINE const Float3& Vertex::tangentU()
//{
//	return _tangentU;
//}
//
//SUMINLINE const Float2& Vertex::texC()
//{
//	return _texC;
//}

