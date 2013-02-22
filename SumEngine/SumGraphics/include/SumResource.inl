//*************************************************************************************************
// Title: SumResource.inl
// Author: Gael Huber
// Description: An engine resource of any given type. This serves as a template for loading
//	specific resources.
//*************************************************************************************************

//*************************************************************************************************
// Constructor
//*************************************************************************************************
template <typename Type>
Resource<Type>::Resource()
	: _resource(0), _name(""), _filePath(""), _isLoaded(false)
{ }

//*************************************************************************************************
// Constructor
//*************************************************************************************************
template <typename Type>
Resource<Type>::Resource(const String& name, const String& filePath, const String& fileType)
	: _resource(0), _name(name), _filePath(filePath), _fileType(fileType), _isLoaded(false)
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
template <typename Type>
Resource<Type>::~Resource()
{
	// Release the resource
	unload();
}

//*************************************************************************************************
// Get the resource
//*************************************************************************************************
template <typename Type>
Type* Resource<Type>::resource()
{
	// If the resource is not loaded, do so
	if(!_isLoaded)
	{
		_load();
		_isLoaded = true;
	}

	// Return the resources
	return _resource;
}

//*************************************************************************************************
// Get the name
//*************************************************************************************************
template <typename Type>
const String& Resource<Type>::name() const
{
	return _name;
}

//*************************************************************************************************
// Get the resource path
//*************************************************************************************************
template <typename Type>
const String& Resource<Type>::filePath() const
{
	return _filePath;
}

//*************************************************************************************************
// Get the resource type
//*************************************************************************************************
template <typename Type>
const String& Resource<Type>::fileType() const
{
	return _fileType;
}
	
//*************************************************************************************************
// Get whether the resource is loaded
//*************************************************************************************************
template <typename Type>
const SBOOL Resource<Type>::isLoaded() const
{
	return _isLoaded;
}

//*************************************************************************************************
// Load the resource
//*************************************************************************************************
template <typename Type>
void Resource<Type>::load()
{ }

//*************************************************************************************************
// Free the resource
//*************************************************************************************************
template <typename Type>
void Resource<Type>::unload()
{ }