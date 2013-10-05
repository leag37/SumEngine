//*************************************************************************************************
// Title: SumDelegate2.inl
// Author: Gael Huber
// Description: Definition for a two parameter delegate
//*************************************************************************************************

//*************************************************************************************************
// Constructor
//*************************************************************************************************
template <typename Param1, typename Param2>
SUMINLINE Delegate2<Param1, Param2>::Delegate2()
	: Delegate()
{ }

//*************************************************************************************************
// Copy constructor
//*************************************************************************************************
template <typename Param1, typename Param2>
SUMINLINE Delegate2<Param1, Param2>::Delegate2(const Delegate2<Param1, Param2>& rhs)
{
	_closure.clear();
	_closure = rhs._closure;
	_param1 = rhs._param1;
	_param2 = rhs._param2;
}

//*************************************************************************************************
// Constructor for non-const member functions
//*************************************************************************************************
template <typename Param1, typename Param2>
template <typename X>
SUMINLINE Delegate2<Param1, Param2>::Delegate2(X* pThis, void (X::*function)(Param1 p1, Param2 p2))
{
	_closure.bind(pThis, function);
}

//*************************************************************************************************
// Constructor for non-const member functions
//*************************************************************************************************
template <typename Param1, typename Param2>
template <typename X>
SUMINLINE Delegate2<Param1, Param2>::Delegate2(X *pThis, void (X::*function)(Param1 p1, Param2 p2), Param1 param1, Param2 param2)
	: _param1(param1), _param2(param2)
{ 
	_closure.bind(pThis, function);
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
template <typename Param1, typename Param2>
SUMINLINE Delegate2<Param1, Param2>::~Delegate2()
{ }

//*************************************************************************************************
// Invoke the delegate
//*************************************************************************************************
template <typename Param1, typename Param2>
SUMINLINE void Delegate2<Param1, Param2>::operator() () const
{
	this->operator()(_param1, _param2);
}

//*************************************************************************************************
// Invoke the delegate with parametrized data
//*************************************************************************************************
template <typename Param1, typename Param2>
SUMINLINE void Delegate2<Param1, Param2>::operator() (Param1 p1, Param2 p2) const
{
	return (_closure.pThis()->*(reinterpret_cast<GenericMemberFunction>(_closure.pFunction())))(p1, p2);
}

//*************************************************************************************************
// Clone
//*************************************************************************************************
template <typename Param1, typename Param2>
SUMINLINE Delegate* Delegate2<Param1, Param2>::clone()
{
	return static_cast<Delegate*>(new Delegate2(*this));
}

//*************************************************************************************************
// Set param1
//*************************************************************************************************
template <typename Param1, typename Param2>
SUMINLINE void Delegate2<Param1, Param2>::setParam1(Param1 param)
{
	_param1 = param;
}

//*************************************************************************************************
// Set param2
//*************************************************************************************************
template <typename Param1, typename Param2>
SUMINLINE void Delegate2<Param1, Param2>::setParam2(Param2 param)
{
	_param2 = param;
}