#include <iostream>
#include <vector>
#include <string>

namespace
{
    struct vector2
    {
        int y, x;

        vector2(int y = 0, int x = 0) : y(y), x(x) {}

        vector2 operator+(const vector2 &other) const
        {
            return vector2(y + other.y, x + other.x);
        }

        vector2 &operator+=(const vector2 &other)
        {
            y += other.y;
            x += other.x;
            return *this;
        }

        bool operator==(const vector2 &other) const
        {
            return y == other.y && x == other.x;
        }
    };
}

int main()
{
    const int DIRECTIONS = 4;
    const vector2 DIRECTION_VECTORS[DIRECTIONS] = {
        vector2(-1, 0), // UP
        vector2(1, 0),  // DOWN
        vector2(0, -1), // LEFT
        vector2(0, 1)   // RIGHT
    };

    const char PERSON = 'A';
    const char TREE = 'T';
    const char GROUND = '.';
    const char VISIBLE = 'V';

    int H, W;
    std::cin >> H >> W;

    std::vector<std::vector<char>> grid(H, std::vector<char>(W));
    std::string str;
    vector2 person_pos;

    for (int y = 0; y < H; ++y)
    {
        std::cin >> str;
        for (int x = 0; x < W; ++x)
        {
            grid[y][x] = str[x];
            if (str[x] == PERSON)
            {
                person_pos = vector2(y, x);
            }
        }
    }

    auto is_in_bounds = [&](const vector2 &pos)
    {
        return pos.y >= 0 && pos.y < H && pos.x >= 0 && pos.x < W;
    };

    auto is_tree = [&](const vector2 &pos)
    {
        return grid[pos.y][pos.x] == TREE;
    };

    for (int dir = 0; dir < DIRECTIONS; ++dir)
    {
        vector2 current_pos = person_pos + DIRECTION_VECTORS[dir];

        while (is_in_bounds(current_pos))
        {
            if (is_tree(current_pos))
                break;

            if (grid[current_pos.y][current_pos.x] == GROUND)
            {
                grid[current_pos.y][current_pos.x] = VISIBLE;
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