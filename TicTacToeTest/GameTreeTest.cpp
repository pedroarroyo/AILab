#include "stdafx.h"

#include "GameTree.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TicTacToeTest
{
	[TestClass]
	public ref class GameTreeTest
	{
	public: 
		[TestMethod]
		void TestChildNodeGeneration()
		{
			TicTacToe::PlayerDesignation player = TicTacToe::kPlayerX;
			GameBoard gameBoard(3);
			GameBoard::Location move(0, 0);
			gameBoard.SetValue( 0 , 0, player );
			GameTreeNode parentNode(player, gameBoard, move);
			
			std::vector<GameTreeNode> childNodes;
			parentNode.GenerateChildNodes(childNodes);

			Assert::AreEqual<char>( childNodes.size(), gameBoard.GetBoardSize() * gameBoard.GetBoardSize() - gameBoard.GetNumOccupiedSquares() );

			for each( const GameTreeNode& childNode in childNodes )
			{
				Assert::AreEqual<char>(TicTacToe::kPlayerO, childNode.m_player );
				Assert::AreEqual<int>( 2, childNode.m_gameBoard.GetNumOccupiedSquares() );
			}
		}
	};
}
