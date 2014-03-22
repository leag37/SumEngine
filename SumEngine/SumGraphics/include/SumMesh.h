//*************************************************************************************************
// Title: SumMesh.h
// Author: Gael Huber
// Description: Contains basic mesh data.
//
// TODO: Write unload function for mesh
//*************************************************************************************************
#ifndef __SUMMESH_H__
#define __SUMMESH_H__

#include "SumResource.h"
#include "SumVertexHardwareBuffer.h"
#include "SumVertexDescription.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	//class SubMesh;

	class Mesh : public Resource
	{
	private:
		/** Predefine a mesh serializer class. This class should only be used within mesh context
		*/
		class MeshSerializer;

	public:
		/** Default constructor
		*/
		Mesh();

		/** Constructor
		* @param
		*	name The name of this resource
		* @param
		*	parentGroup The parent group for this resource
		*/
		Mesh(const String& name, ResourceGroup* parentGroup);

		/** Constructor
		* @param
		*	name The name of this resource
		* @param
		*	parentGroup The parent group for this resource
		* @param
		*	fullName The full name of the file associated with this resource
		*/
		Mesh(const String& name, ResourceGroup* parentGroup, const String& fullName);

		/** Destructor
		*/
		virtual ~Mesh();

		/** Load the resource
		*/
		void load();

		/** Unload the resource
		*/
		void unload();

	protected:
		/** List of submeshes composing this mesh
		*/
		//List<SubMesh*> _subMeshes;

		/** Hardware buffer for vertices
		*/
		//VertexHardwareBufferPtr _vertexHardwareBuffer;

		/** The vertex definition
		*/
		VertexDescription _vertexDescription;
	};

	/*
	class Mesh //: public BaseResource
	{
	public:
		// Constructor
		Mesh();

		// Constructor
		Mesh(const String& name, const String& filePath, const String& fileType);

		// Constructor from name
		Mesh(const String& name);

		// Create the mesh
		Mesh(const String& name, ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, SUINT vertexCount, SUINT indexCount);

		// Destructor
		~Mesh();

		// Load the mesh
		void load();

		// Free the mesh
		void unload();

		// Return the mesh data for this object
		const MeshData& getMeshData() const;

	private:
		// Vertex buffer
		ID3D11Buffer* _vertexBuffer;

		// Index buffer
		ID3D11Buffer* _indexBuffer;

		// Vertex count
		SUINT _vertexCount;

		// Index count
		SUINT _indexCount;

		// Mesh data for this mesh
		MeshData _data;

	// Inline functions
	public:
		SUMINLINE ID3D11Buffer* vertexBuffer()
		{
			return _vertexBuffer;
		}

		// Return the vertex buffer
		SUMINLINE ID3D11Buffer** vertexBufferPtr()
		{
			return &_vertexBuffer;
		}

		// Release the existing buffer and set the new one
		SUMINLINE void vertexBuffer(ID3D11Buffer* rhs)
		{
			ReleaseCOM(_vertexBuffer);
			_vertexBuffer = rhs;
		}

		// Return the index buffer
		SUMINLINE ID3D11Buffer* indexBuffer() const
		{
			return _indexBuffer;
		}

		// Release the existing buffer and set the new one
		SUMINLINE void indexBuffer(ID3D11Buffer* rhs)
		{
			ReleaseCOM(_indexBuffer);
			_indexBuffer = rhs;
		}

		// Get the vertex count
		SUMINLINE SUINT vertexCount() const
		{
			return _vertexCount;
		}

		// Set the vertex count
		SUMINLINE void vertexCount(SUINT rhs)
		{
			_vertexCount = rhs;
		}

		// Return the index count
		SUMINLINE SUINT indexCount() const
		{
			return _indexCount;
		}

		// Set the index count
		SUMINLINE void indexCount(SUINT rhs)
		{
			_indexCount = rhs;
		}

		// Return the mesh data
		SUMINLINE const MeshData& data() const
		{
			return _data;
		}
	
	};*/

	/** @} */

}	// Namespace

#endif	// __SUMMESH_H__