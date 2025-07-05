#include <iostream>
#include <vector>
#include <string>
#include <array>

namespace
{
    struct vector2
    {
        int y, x;

        vector2(int y = 0, int x = 0) : y(y), x(x) {}

        auto operator+(const vector2 &other) const -> vector2
        {
            return {y + other.y, x + other.x};
        }

        auto operator+=(const vector2 &other) -> vector2 &
        {
            y += other.y;
            x += other.x;
            return *this;
        }

        auto operator==(const vector2 &other) const -> bool
        {
            return y == other.y && x == other.x;
        }
    };
}

auto main() -> int
{
    const int DIRECTIONS = 4;
    const std::array<vector2, DIRECTIONS> DIRECTION_VECTORS = {
        vector2(-1, 0), // UP
        vector2(1, 0),  // DOWN
        vector2(0, -1), // LEFT
        vector2(0, 1)   // RIGHT
    };

    const char PERSON = 'A';
    const char TREE = 'T';
    const char GROUND = '.';
    const char VISIBLE = 'V';

    int height = 0;
    int width = 0;
    std::cin >> height >> width;

    std::vector<std::vector<char>> grid(static_cast<std::size_t>(height), std::vector<char>(static_cast<std::size_t>(width)));
    std::string str;
    vector2 person_pos;

    for (int iy = 0; iy < height; ++iy)
    {
        std::cin >> str;
        for (int ix = 0; ix < width; ++ix)
        {
            grid[static_cast<std::size_t>(iy)][static_cast<std::size_t>(ix)] = str[static_cast<std::size_t>(ix)];
            if (str[static_cast<std::size_t>(ix)] == PERSON)
            {
                person_pos = vector2(iy, ix);
            }
        }
    }

    auto is_in_bounds = [&](const vector2 &pos)
    {
        return pos.y >= 0 && pos.y < height && pos.x >= 0 && pos.x < width;
    };

    auto is_tree = [&](const vector2 &pos)
    {
        return grid[static_cast<std::size_t>(pos.y)][static_cast<std::size_t>(pos.x)] == TREE;
    };

    for (std::size_t dir = 0; dir < DIRECTIONS; ++dir)
    {
        vector2 current_pos = person_pos + DIRECTION_VECTORS[dir];

        while (is_in_bounds(current_pos))
        {
            if (is_tree(current_pos))
            {
                break;
            }

            if (grid[static_cast<std::size_t>(current_pos.y)][static_cast<std::size_t>(current_pos.x)] == GROUND)
            {
                grid[static_cast<std::size_t>(current_pos.y)][static_cast<std::size_t>(current_pos.x)] = VISIBLE;
            }

            current_pos += DIRECTION_VECTORS[dir];
        }
    }

    for (const auto &row : grid)
    {
        for (char c : row)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    return 0;
}