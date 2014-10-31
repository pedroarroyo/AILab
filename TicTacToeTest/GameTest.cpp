#include "stdafx.h"

#include "Game.h"
#include "GameBoard.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TicTacToeTest
{
	class TestGame : public Game
	{
	public:
		TestGame() : Game(3, kPlayerStrategyTypeHuman, kPlayerStrategyTypeHuman) {}



	};


	[TestClass]
	public ref class GameTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		[TestMethod]
		void TestVictoryConditions()
		{
			TestGame testGame;
			
		};
	};
}
