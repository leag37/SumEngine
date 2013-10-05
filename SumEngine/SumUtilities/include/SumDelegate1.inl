//*************************************************************************************************
// Title: SumDelegate1.inl
// Author: Gael Huber
// Description: Definition for a single parameter delegate
//*************************************************************************************************

//*************************************************************************************************
// Constructor
//*************************************************************************************************
template <typename Param1>
SUMINLINE Delegate1<Param1>::Delegate1()
	: Delegate()
{ }

//*************************************************************************************************
// Copy constructor
//*************************************************************************************************
template <typename Param1>
SUMINLINE Delegate1<Param1>::Delegate1(const Delegate1<Param1>& rhs)
{
	_closure.clear();
	_closure = rhs._closure;
	_param1 = rhs._param1;
}

//*************************************************************************************************
// Constructor for non-const member functions
//*************************************************************************************************
template <typename Param1>
template <typename X>
SUMINLINE Delegate1<Param1>::Delegate1(X* pThis, void (X::*function)(Param1 p1))
{
	_closure.bind(pThis, function);
}

//*************************************************************************************************
// Constructor for non-const member functions
//*************************************************************************************************
template <typename Param1> 
template <typename X>
SUMINLINE Delegate1<Param1>::Delegate1(X *pThis, void (X::*function)(Param1 p1), Param1 param1)
	: _param1(param1)
{ 
	_closure.bind(pThis, function);
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
template <typename Param1>
SUMINLINE Delegate1<Param1>::~Delegate1()
{ }

//*************************************************************************************************
// Invoke the delegate
//*************************************************************************************************
template <typename Param1>
SUMINLINE void Delegate1<Param1>::operator() () const
{
	this->operator()(_param1);
}

//*************************************************************************************************
// Invoke the delegate with parametrized data
//*************************************************************************************************
template <typename Param1>
SUMINLINE void Delegate1<Param1>::operator() (Param1 p1) const
{
	return (_closure.pThis()->*(reinterpret_cast<GenericMemberFunction>(_closure.pFunction())))(p1);
}

//*************************************************************************************************
// Clone
//*************************************************************************************************
template <typename Param1>
SUMINLINE Delegate* Delegate1<Param1>::clone()
{
	return static_cast<Delegate*>(new Delegate1(*this));
}

//*************************************************************************************************
// Set param1
//*************************************************************************************************
template <typename Param1>
SUMINLINE void Delegate1<Param1>::setParam1(Param1 param)
{
	_param1 = param;
}