#include "stdafx.h"

#include "GameBoard.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TicTacToeTest
{
	[TestClass]
	public ref class GameBoardTest
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

		#pragma region Additional test attributes
		#pragma endregion 

		[TestMethod]
		void InitializationTest()
		{
			GameBoard testBoard(3);
			Assert::AreEqual<uint8_t>(testBoard.GetNumOccupiedSquares(), 0);

			Assert::AreEqual<char>(TicTacToe::kInvalidPlayer, testBoard.GetValue(0, 0));
		};

		[TestMethod]
		void SetValueTest()
		{
			GameBoard testBoard(3);

			testBoard.SetValue(0, 0, TicTacToe::kPlayerO);
			Assert::AreEqual<char>(TicTacToe::kPlayerO, testBoard.GetValue(0, 0));
			Assert::AreEqual<uint8_t>(testBoard.GetNumOccupiedSquares(), 1);

			testBoard.SetValue(1, 1, TicTacToe::kPlayerX);
			Assert::AreEqual<char>(TicTacToe::kPlayerX, testBoard.GetValue(1, 1));
			Assert::AreEqual<uint8_t>(testBoard.GetNumOccupiedSquares(), 2);
		};

		[TestMethod]
		void SetValueOutOfBoundsTest()
		{
			GameBoard testBoard(3);

			testBoard.SetValue(0, 0, TicTacToe::kPlayerO);
			Assert::AreEqual<char>(TicTacToe::kPlayerO, testBoard.GetValue(0, 0));
			Assert::AreEqual<uint8_t>(testBoard.GetNumOccupiedSquares(), 1);


			Assert::AreEqual<bool>(false, testBoard.SetValue(5, 5, TicTacToe::kPlayerO));
			Assert::AreEqual<bool>(false, testBoard.SetValue(4, 3, TicTacToe::kPlayerX));
		};
	};
}
