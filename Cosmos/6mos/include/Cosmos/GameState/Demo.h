#ifndef DEMO_H
#define DEMO_H
#include "Cosmos/GameState/GameState.h"
namespace Game::GS
{
	using Game::Cosmos;

	class Demo : public GameState
	{
		//could be private tho right? lol :)
	public:
		void Init(Cosmos& Cosmos);

		void Cleanup() {}

		void Pause() {}

		void Resume(Cosmos& Cosmos) {}

		void UpdateGameStateObjects(Cosmos& Cosmos);
		void UpdateMenuObjects(Cosmos& Cosmos) { }

		void AddGameStateObjectsToPipeline(Cosmos& Cosmos);
		void AddMenuObjectsToPipeline(Cosmos& Cosmos) { }

		static Demo* Instance()
		{
			if (m_Demo == nullptr)
			{
				m_Demo = new Demo();
			}
			return m_Demo;
		}
	private:
		Demo() { }
		Demo(const Demo& obj) {}
		static Demo* m_Demo;
	};
}
#endif
