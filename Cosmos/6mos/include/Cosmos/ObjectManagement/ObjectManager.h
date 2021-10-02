#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
#include "Cosmos/ObjectManagement/Object.h"
#include "Cosmos/ObjectManagement/ObjectType.h"
#include "Cosmos/ObjectManagement/ObjectUpdateRuleset.h"
#include <vector>
namespace Game::ObjectManagement
{
	class ObjectManager
	{
	public:
		void AddObjectStream(ObjectType, const ObjectUpdateRuleset&);
		void UpdateObjectStreams(); //Updates all streams of type ObjectType
	private:
		std::vector<std::vector<Object*>> vecOfvecObjectStreams;
		//concurrent ruleset vector
		std::vector<ObjectUpdateRuleset> vecRuleset;
	};
}
#endif //OBJECT_MANAGER_H
