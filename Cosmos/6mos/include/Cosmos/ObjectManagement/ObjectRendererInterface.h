#ifndef OBJECT_RENDERER_H
#define OBJECT_RENDERER_H

namespace Game::ObjectManagement
{
	class ObjectRendererInterface
	{
	public:
		/*Can add any objecttype stream with its type specific stream modifications*/

		//AddObjectStream
		//SetObjectStreamProperties


		virtual void AddObjectStream() = 0;
		virtual void SetObjectStreamProperties() = 0;

		//can also sort render position based on a priority
		virtual void RenderAll() = 0;

	};
}
#endif //Object Renderer