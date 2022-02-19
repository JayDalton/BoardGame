
#include <array>
#include <iostream>
#include <format>

enum class State { None, Cross, Circle };

struct Plate
{
   State state{};

};

struct GameBoard
{
   static constexpr std::uint8_t m_size{ 3 };
   std::array<Plate, m_size * m_size> m_board;

   const Plate& at(std::uint8_t r, std::uint8_t c) const
   {
      return m_board.at(r * m_size + c);
   }

   Plate& at(std::uint8_t r, std::uint8_t c)
   {
      return m_board.at(r * m_size + c);
   }
};

void draw(const Plate& plate)
{

}

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
         std::cout << std::format("{: ^5}", row * board.m_size + col + 1);
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

int readNumberInput()
{
   while (true)
   {
      try
      {
         std::string input;
         std::cout << std::format("{:10}", "input:");
         std::getline(std::cin, input);
         return std::stoi(input);
      }
      catch (...) {}
   }
}

auto main(int, char* []) -> int
{
   GameBoard board{};

   draw(board);

   readNumberInput();

   return 0;
}

