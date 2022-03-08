
#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <numeric>
#include <ranges>
#include <unordered_map>
#include <variant>

//enum class State { Empty, Cross, Circle };

struct State
{
   char ident{ '0' };
   auto operator<=>(const State&) const = default;
   explicit operator bool() const { return ident != -1; }
};

struct Player
{
   std::string label;
   char symbol{ '0' };
   auto toString() const
   {
      return std::format("{} [{}]", label, symbol);
   }
};

struct GameBoard
{
   static constexpr std::uint8_t m_size{ 3 };
   std::array<char, m_size * m_size> m_board;

   GameBoard() {
      std::iota(m_board.begin(), m_board.end(), '1');
   }

   char at(std::uint8_t r, std::uint8_t c) const
   {
      return m_board.at(r * m_size + c);
   }

   char& at(std::uint8_t r, std::uint8_t c)
   {
      return m_board.at(r * m_size + c);
   }

   bool contains(char symbol) const
   {
      auto pred = [&](char field) { return field == symbol; };
      return std::any_of(m_board.cbegin(), m_board.cend(), pred);
   }

   void replace(int oldSymbol, int newSymbol)
   {
      std::replace(m_board.begin(), m_board.end(), oldSymbol, newSymbol);
   }
};

void draw(const GameBoard& board)
{
   auto PrintSpace = [](int size) {
      std::cout << std::format("{:{}}", ' ', size);
   };

   std::cout << std::format("{: ^50}", "Tic -- Tac -- Toe") << std::endl;
   std::cout << std::format("{: ^50}", "for 2 Payers") << std::endl;
   std::cout << std::format("{: ^50} {}", "Player - 1 [X]", "Player - 2 [O]") << std::endl;

   for (auto row{ 0 }; row < board.m_size; row++)
   {
      std::cout << std::endl 
         << std::format("{:>15}", ' ')
         << std::format("{:>5}|", ' ')
         << std::format("{:>5}|", ' ')
         ;
      
      std::cout << std::endl << std::format("{:>15}", ' ');
      for (auto col{ 0 }; col < board.m_size; col++)
      {
         std::cout << std::format("{: ^5}", board.at(row, col));
         if (col + 1 < board.m_size)
         {
            std::cout << "|";
         }
      }
      std::cout << std::format("") << std::endl;

      if (row + 1 < board.m_size)
      {
         std::cout
            << std::format("{:>15}", ' ')
            << std::format("{:_>5}|", '_')
            << std::format("{:_>5}|", '_')
            << std::format("{:_>5}", '_');
      }
      else
      {
         std::cout
            << std::format("{:>15}", ' ')
            << std::format("{:>5}|", ' ')
            << std::format("{:>5}|", ' ')
            << std::format("{:>5}", ' ');

      }
   }

   std::cout << std::endl << std::endl << std::endl;
}

int readPlayerInput(const Player& player)
{
   while (true)
   {
      try
      {
         std::string input;
         std::cout << std::format("Player {} must select next Field\n", player.toString());
         std::cout << std::format("Select FiledNumber [Range: 1-9, 0 = exit]: ");
         std::getline(std::cin, input);
         return std::stoi(input);
      }
      catch (...) {
         std::cout << " Falsche Eingabe!" << std::endl;
      }
   }
}

bool askPlayerAction()
{
   while (true)
   {
      try
      {
         std::string input;
         std::cout << std::format("Game ends, new one? [y/n]");
         std::getline(std::cin, input);
         return std::stoi(input);
      }
      catch (...) {
         std::cout << " Falsche Eingabe!" << std::endl;
      }
   }
}

struct Game
{
   int playGame()
   {
      draw(m_board);

      bool running{ true };
      while (running)
      {
         draw(m_board);

         if (auto in = readPlayerInput(m_player.at(0)))
         {
            auto symbol{ in + '0' };
            if (m_board.contains(symbol))
            {
               m_board.replace(symbol, m_player.at(0).symbol);
               NextPlayer();
            }
            else
            {
               std::cout << "Eingabe unbekannt" << std::endl << std::endl;
            }
         }
         else
         {
            running = false;
         }

         analyze(board);
      }
      return {};
   }

   int run()
   {
      bool running{ true };
      while (running)
      {
         if (auto result = playGame())
         {
            std::cout << std::format("Player {} wins!") << std::endl;
         }
         else
         {
            std::cout << std::format("Unentschieden ...!") << std::endl;
         }

         // Noch ein Spiel?
         m_board = GameBoard{};
         if (auto res = readPlayerInput())
         {
            running = false;
         }
      }

      return {};
   }

private:
   void NextPlayer() {
      std::rotate(m_player.begin(), m_player.begin() + 1, m_player.end());
   }

private:
   GameBoard m_board{};
   std::vector<Player> m_player{
      Player{ "Spieler 1", 'X' },
      Player{ "Spieler 2", 'O' } };
};

auto main(int, char* []) -> int
{
   Game game{};
   return game.run();
}

