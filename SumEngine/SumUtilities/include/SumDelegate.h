//*************************************************************************************************
// Title: SumDelegate.h
// Author: Gael Huber
// Description: Delegates permit binding and execution of functions in a general state, acting as
//	general-purpose function templates.
//
// TODO: Split various details out into seperate files
//*************************************************************************************************
#ifndef __SUMDELEGATE_H__
#define __SUMDELEGATE_H__

#include "SumInclude.h"

// Hide main functionality within a namespace
namespace delegate_details
{
	// Define a generic class
	class __single_inheritance GenericClass;

	// Define a generic member function pointer
	typedef void (GenericClass::*GenericMemberFunctionPtr)();

	// Implicit cast from a given type to another
	template <class OutputClass, class InputClass>
	OutputClass implicit_cast(InputClass input);

	// Union between two classes
	template <class OutputClass, class InputClass>
	union ClassUnion
	{
		OutputClass out;
		InputClass in;
	};

	// Class Cast between two classes
	template <class OutputClass, class InputClass>
	OutputClass class_cast(InputClass input);

	// Class that provides closure for class delegates
	class Closure
	{
	private:
		// Pointer to the class instance
		GenericClass* _this;

		// Pointer to function
		GenericMemberFunctionPtr _function; 

	public:
		// Constructor
		Closure();

		// Copy constructor
		Closure(const Closure& rhs);

		// Assignment operator
		Closure& operator=(const Closure& rhs);

		// Bind	the functions
		template <typename X, typename XMemFunc>
		void bind(X instance, XMemFunc function);

		// Clear the functions
		void clear();

	// Inline functions
	public:
		// Return an instance of this class
		GenericClass* pThis() const;

		// Return an instance of the function pointer
		GenericMemberFunctionPtr pFunction() const;
	};
}

using namespace delegate_details;

// Basic delegate
class Delegate
{
public:
	// Constructor
	Delegate();

	// Copy constructor
	Delegate(const Delegate& rhs);

	// Constructor for non-const member functions
	template <typename X>
	Delegate(X* pThis, void (X::*function)());

	// Destructor
	~Delegate();

	// Invoke the delegate
	virtual void operator() () const;

	// Virtual clone function
	virtual Delegate* clone();

protected:
	// Closure for the delegate
	Closure _closure;
};

// Delegate with no parameter
template <typename Param1>
class Delegate1 : public Delegate
{
private:
	typedef void (delegate_details::GenericClass::*GenericMemberFunction)(Param1 p1);

public:
	// Constructor
	Delegate1();

	// Copy constructor
	Delegate1(const Delegate1& rhs);

	// Constructor for non-const member functions
	template <typename X>
	Delegate1(X* pThis, void (X::*function)(Param1 p1));

	// Constructor for non-const member functions with pre-set data (useful for calling the function asynchronously)
	template <typename X>
	Delegate1(X *pThis, void (X::*function)(Param1 p1), Param1 param1);

	// Destructor
	~Delegate1();

	// Invoke the delegate
	void operator() () const;

	// Invoke the delegate with parametrized data
	void operator() (Param1 p1) const;

	// Virtual clone function
	Delegate* clone();

	// Set param1
	void setParam1(Param1 param);

private:
	// Closure for the delegate
	Param1 _param1;
};

#include "SumDelegate.inl"

#endif