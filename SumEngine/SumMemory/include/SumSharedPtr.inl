//*************************************************************************************************
// Title: SumSharedPtr.inl
// Author: Gael Huber
// Description: A base class for shared pointer objects.
//*************************************************************************************************

namespace SumEngine
{

	//*************************************************************************************************
	// Base constructor. This should generally speaking not be used. 
	//*************************************************************************************************
	template <class Type>
	SharedPtr<Type>::SharedPtr()
		:	_pType(0),
			_refCount(0)
	{ }

	//*************************************************************************************************
	// Primary constructor, pass in a reference to the object
	// @param
	//	pType The pointer to the object being owned
	//*************************************************************************************************
	template <class Type>
	SharedPtr<Type>::SharedPtr(Type* pType)
		:	_pType(pType),
			_refCount(_pType ? new SUINT(1) : 0)
	{ }

	//*************************************************************************************************
	// Copy constructor
	//*************************************************************************************************
	template <class Type>
	SharedPtr<Type>::SharedPtr(const SharedPtr& rhs)
		:	_pType(rhs._pType),
			_refCount(rhs._refCount)
	{ 
		// Increment ref count
		if(_refCount != 0)
		{
			++(*_refCount);
		}
	}

	//*************************************************************************************************
	// Assignment operator
	//*************************************************************************************************
	template <class Type>
	SharedPtr<Type>& SharedPtr<Type>::operator=(const SharedPtr& rhs)
	{
		if(this == &rhs)
		{
			return *this;
		}

		_pType = rhs._pType;
		_refCount = rhs._refCount;

		return *this;
	}

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	template <class Type>
	SharedPtr<Type>::~SharedPtr()
	{
		release();
	}

	//*************************************************************************************************
	// Getter for the data as a pointer
	// @return
	//	Type* Return a pointer to the data
	//*************************************************************************************************
	template <class Type>
	Type* SharedPtr<Type>::operator->() const
	{
		return _pType;
	}

	//*************************************************************************************************
	// Getter for the data pointer directly
	// @return
	//	Type* Return a pointer to the data
	//*************************************************************************************************
	template <class Type>
	Type* SharedPtr<Type>::get() const
	{
		return _pType;
	}

	//*************************************************************************************************
	// Getter for the data by reference
	// @return
	//	Type& Return a reference to the data
	//*************************************************************************************************
	template <class Type>
	Type& SharedPtr<Type>::operator*() const
	{
		return *_pType;
	}

	//*************************************************************************************************
	// Check if the data is unique
	// @return
	//	SBOOL True if there is only one reference, false otherwise
	//*************************************************************************************************
	template <class Type>
	SBOOL SharedPtr<Type>::isUnique() const
	{
		return (_refCount) ? (*_refCount == 1) : false;
	}

	//*************************************************************************************************
	// Get the number of references
	// @return
	//	SUINT The number of references to this pointer
	//*************************************************************************************************
	template <class Type>
	SUINT SharedPtr<Type>::getRefCount() const
	{
		return _refCount ? *_refCount : 0;
	}

	//*************************************************************************************************
	// Check if the pointer is null
	// @return
	//	SBOOL True if null, false otherwise
	//*************************************************************************************************
	template <class Type>
	SBOOL SharedPtr<Type>::isNull() const
	{
		return _pType == 0;
	}

	//*************************************************************************************************
	// Set this pointer to null
	//*************************************************************************************************
	template <class Type>
	void SharedPtr<Type>::setNull()
	{
		if(_pType)
		{
			// Release this pointer
			release();

			// Set the pointer and ref counter to null
			_pType = 0;
			_refCount = 0;
		}
	}

	//*************************************************************************************************
	// Release this pointer and decrement the reference counter by 1
	//*************************************************************************************************
	template <class Type>
	void SharedPtr<Type>::release()
	{
		// Chceck for pointer validity
		if(_pType)
		{
			// Decrement the ref count if it exists
			if(_refCount)
			{
				// Destroy the pointer if the ref count is 0
				if(--(*_refCount) == 0)
				{
					destroy();
				}
			}
		}
	}

	//*************************************************************************************************
	// Ready to destroy the pointer as we have a reference count of 0
	//*************************************************************************************************
	template <class Type>
	void SharedPtr<Type>::destroy()
	{
		// Delete both pType and refCount
		SafeDelete(_pType);
		SafeDelete(_refCount);
	}

}	// Namespace