#ifndef OBJECT_H
#define OBJECT_H
namespace Game::ObjectManagement
{
	class Object
	{
	public:
		virtual void Update() = 0;
		virtual void Render() = 0;
	};
}
#endif //OBJECT_H
