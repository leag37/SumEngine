//*************************************************************************************************
// Title: SumDelegate.inl
// Author: Gael Huber
// Description: Delegates permit binding and execution of functions in a general state, acting as
//	general-purpose function templates.
//*************************************************************************************************

namespace delegate_details
{

//*************************************************************************************************
// Implicit cast from a given type to another
//*************************************************************************************************
template <class OutputClass, class InputClass>
SUMINLINE OutputClass implicit_cast(InputClass input)
{
	return input;
}

//*************************************************************************************************
// Class Cast between two classes
//*************************************************************************************************
template <class OutputClass, class InputClass>
SUMINLINE OutputClass class_cast(InputClass input)
{
	ClassUnion<OutputClass, InputClass> u;
	u.in = input;
	return u.out;
}

//*************************************************************************************************
// Constructor
//*************************************************************************************************
SUMINLINE Closure::Closure()
	:	_this(0),
		_function(0)
{ }

//*************************************************************************************************
// Copy constructor
//*************************************************************************************************
SUMINLINE Closure::Closure(const Closure& rhs)
{
	_this = rhs._this;
	_function = rhs._function;
}

//*************************************************************************************************
// Assignment operator
//*************************************************************************************************
SUMINLINE Closure& Closure::operator=(const Closure& rhs)
{
	_this = rhs._this;
	_function = rhs._function;
	return *this;
}

//*************************************************************************************************
// Bind	the functions
//*************************************************************************************************
template <typename X, typename XMemFunc>
SUMINLINE void Closure::bind(X instance, XMemFunc function)
{
	_this = reinterpret_cast<GenericClass*>(instance);
	_function = class_cast<GenericMemberFunctionPtr>(function);
}

//*************************************************************************************************
// Clear the functions
//*************************************************************************************************
SUMINLINE void Closure::clear()
{
	_this = 0;
	_function = 0;
}

//*************************************************************************************************
// Return an instance of this class
//*************************************************************************************************
SUMINLINE GenericClass* Closure::pThis() const
{
	return _this;
}

//*************************************************************************************************
// Return an instance of the function pointer
//*************************************************************************************************
SUMINLINE GenericMemberFunctionPtr Closure::pFunction() const
{
	return _function;
}

}

//*************************************************************************************************
// Constructor
//*************************************************************************************************
SUMINLINE Delegate::Delegate()
{
	_closure.clear();
}

//*************************************************************************************************
// Copy constructor
//*************************************************************************************************
SUMINLINE Delegate::Delegate(const Delegate& rhs)
{
	_closure.clear();
	_closure = rhs._closure;
}

//*************************************************************************************************
// Constructor for non-const member functions
//*************************************************************************************************
template <typename X>
SUMINLINE Delegate::Delegate(X* pThis, void (X::*function)())
{
	_closure.bind(pThis, function);
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
SUMINLINE Delegate::~Delegate()
{

}

//*************************************************************************************************
// Invoke the delegate
//*************************************************************************************************
SUMINLINE void Delegate::operator() () const
{
	return (_closure.pThis()->*(_closure.pFunction()))();
}

//*************************************************************************************************
// Clone
//*************************************************************************************************
SUMINLINE Delegate* Delegate::clone()
{
	return new Delegate(*this);
}

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

