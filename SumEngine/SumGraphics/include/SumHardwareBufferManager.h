//*************************************************************************************************
// Title: SumHardwareBufferManager.h
// Author: Gael Huber
// Description: A manager for creating and tracking hardware buffers.
//*************************************************************************************************
#ifndef __SUMHARDWAREBUFFERMANAGER_H__
#define __SUMHARDWAREBUFFERMANAGER_H__

#include "SumInclude.h"
#include "SumSingleton.h"
#include "SumVertexHardwareBuffer.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class RenderSystem;

	class HardwareBufferManager : public Singleton<HardwareBufferManager>
	{
	public:
		/** Default constructor
		*/
		HardwareBufferManager();

		/** Constructor based on render system
		* @param
		*	renderSystem The render system currently in use
		*/
		HardwareBufferManager(const RenderSystem* renderSystem);

		/** Singleton accessor
		* @return
		*	HardwareBufferManager& A reference to the buffer manager
		*/
		static HardwareBufferManager& getSingleton();

		/** Singleton pointer accessor
		* @return
		*	HardwareBufferManager* A pointer to the hardware buffer manager
		*/
		static HardwareBufferManager* getSingletonPtr();

		/** Create a vertex buffer
		* @param
		*	vertexSize The size of each vertex
		* @param
		*	numVertices The numer of vertices in the buffer
		* @param
		*	usage The buffer usage type
		*/
		VertexHardwareBuffer* createVertexBuffer(SUINT vertexSize, SUINT numVertices, HardwareBufferUsage usage);

	protected:
		/** The next buffer id to be assigned
		*/
		SUINT16 _nextBufferId;
	};

	/** @} */

}	// Namespace

#endif // __SUMHARDWAREBUFFERMANAGER_H__