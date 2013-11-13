//*************************************************************************************************
// Title: SumSharedPtr.h
// Author: Gael Huber
// Description: A base class for shared pointer objects.
//*************************************************************************************************
#ifndef __SUMSHAREDPTR_H__
#define __SUMSHAREDPTR_H__

#include <assert.h>

namespace SumEngine
{
	/** \addtogroup Memory
	*	@{
	*/

	template <class Type>
	class SharedPtr
	{
	public:
		/** Base constructor. This should generally speaking not be used. */
		SharedPtr();

		/** Primary constructor, pass in a reference to the object
		* @param
		*	pType The pointer to the object being owned
		*/
		explicit SharedPtr(Type* pType);

		/** Copy constructor
		*/
		SharedPtr(const SharedPtr& rhs);

		/** Assignment operator
		*/
		SharedPtr& operator=(const SharedPtr& rhs);

		/** Destructor
		*/
		~SharedPtr();

		/** Getter for the data as a pointer
		* @return
		*	Type* Return a pointer to the data
		*/
		Type* operator->() const;

		/** Getter for the data pointer directly
		* @return
		*	Type* Return a pointer to the data
		*/
		Type* get() const;

		/** Getter for the data by reference
		* @return
		*	Type& Return a reference to the data
		*/
		Type& operator*() const;

		/** Check if the data is unique
		* @return
		*	SBOOL True if there is only one reference, false otherwise
		*/
		SBOOL isUnique() const;

		/** Get the number of references
		* @return
		*	SUINT The number of references to this pointer
		*/
		SUINT getRefCount() const;

		/** Check if the pointer is null
		* @return
		*	SBOOL True if null, false otherwise
		*/
		SBOOL isNull() const;

		/** Set this pointer to null
		*/
		void setNull();

	private:
		/** Release this pointer and decrement the reference counter by 1
		*/
		void release();

		/** Ready to destroy the pointer as we have a reference count of 0
		*/
		void destroy();

	private:
		/** Reference to the object being owned
		*/
		Type* _pType;

		/** The reference counter for this object
		*/
		SUINT* _refCount;
	};

	/** @} */

}	// Namespace

#endif // __SUMSHAREDPTR_H__