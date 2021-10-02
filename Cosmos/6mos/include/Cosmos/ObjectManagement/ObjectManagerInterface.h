#ifndef OBJECT_MANAGER_INTERFACE_H
#define OBJECT_MANAGER_INTERFACE_H
/* The object Manager keeps track of which objects should be added to 
the rendering pipeline */

//In charge of MenuObjects, AmbienceObjects, and GameObjects
namespace Game::ObjectManagement
{
	/* In charge of Ambience + Menu + Game object Entities*/
	class ObjectManagerInterface
	{
	public:
		virtual void Update() = 0;
	};
}
#endif
