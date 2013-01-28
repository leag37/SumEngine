//*************************************************************************************************
// Title: SumDelegate.h
// Author: Gael Huber
// Description: Delegates permit binding and execution of functions in a general state, acting as
//	general-purpose function templates.
//*************************************************************************************************
#ifndef __SUMDELEGATE_H__
#define __SUMDELEGATE_H__

#include "SumInclude.h"

// Hide main functionality within a namespace
namespace delegate_details
{
	// Define a generic class
	class __single_inheritance GenericClass;

	// Implicit cast from a given type to another
	template <class OutputClass, class InputClass>
	SUMINLINE OutputClass implicit_cast(InputClass input)
	{
		return input;
	}

	// Class that provides closure for class delegates
	class Closure
	{
	private:
		// Define a generic member function pointer
		typedef void (GenericClass::*GenericMemberFunctionPtr)();

		// Pointer to the class instance
		GenericClass* _this;

		// Pointer to function
		GenericMemberFunctionPtr _function; 

	public:
		// Constructor
		SUMINLINE Closure()
			:	_this(0),
				_function(0)
		{ }

		// Bind	the functions
		template <typename X, typename XMemFunc>
		SUMINLINE void bind(X instance, XMemFunc function)
		{
			_this = reinterpret_cast<GenericClass*>(instance);
			_function = reinterpret_cast<GenericMemberFunctionPtr>(function);
		}

		// Clear the functions
		SUMINLINE void clear()
		{
			_this = 0;
			_function = 0;
		}

	// Inline functions
	public:
		// Return an instance of this class
		SUMINLINE GenericClass* pThis() const
		{
			return _this;
		}

		// Return an instance of the function pointer
		SUMINLINE GenericMemberFunctionPtr pFunction() const
		{
			return _function;
		}
	};
}

using namespace delegate_details;

// Delegate with no parameter
class Delegate0
{
public:
	// Constructor
	SUMINLINE Delegate0()
	{
		_closure.clear();
	}

	// Constructor for non-const member functions
	template <typename X, typename Y>
	SUMINLINE Delegate0(Y *pThis, void (X::*function)())
	{
		_closure.bind(implicit_cast<X*>(pThis), function);
	}

	// Bind function for non-const member function
	SUMINLINE void bind()
	{

	}

	// Invoke the delegate
	SUMINLINE void operator() () const
	{
		return (_closure.pThis()->*(_closure.pFunction()))();
	}

private:
	// Closure for the delegate
	Closure _closure;
};

#endif