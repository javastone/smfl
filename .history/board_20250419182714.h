//
// Created by sophi on 4/17/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "tile.h"

class Board
{
    vector<tile> tiles;
    int rows, cols, mines;
    sf::Texture hiddenTexture, revealedTexture, mineTexture, flagTexture, num1Txture, num2Txture, num3Txture, num4Txture, num5Txture, num6Txture, num7Txture, num8Txture;
    int gameStatus;
    //1 = win, 2 = fail, 0 = playing
public:
    Board() {};
    Board(int c, int r, int m) : cols(c), rows(r), mines(m)
    {
        gameStatus = 0;
        cout << " cols: " << cols << "rows: " << rows << " mines: " << mines << endl;
        loadTextures();
        vector<int> minePosition = generate_unique_random_numbers();
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                tile tile(c, r);
                bool isMine = isIntInVector(minePosition, r * cols + c);
                tile.setMineState(isMine);
                int total = countMinesAround(r * cols + c, minePosition);
                tile.setMinesAround(total);
                tiles.push_back(tile);
            }
        }
    }

    vector<tile> getTiles()
    {
        return tiles;
    }
    int getRows()
    {
        return rows;
    }
    int getCols()
    {
        return cols;
    }

    int getStatus() {
        return gameStatus;
    }

    void setStatus(int status) {
        gameStatus = status;
    }

    // generate random mine indexes
    vector<int> generate_unique_random_numbers()
    {
        vector<int> numbers(rows * cols);
        iota(numbers.begin(), numbers.end(), 1);
        random_device rd;
        mt19937 generator(time(0));
        shuffle(numbers.begin(), numbers.end(), generator);

        return vector<int>(numbers.begin(), numbers.begin() + mines);
    }

    bool isIntInVector(const vector<int> &vec, int value)
    {
        for (int i : vec)
        {
            if (i == value)
            {
                return true;
            }
        }
        return false;
    }

    int countMinesAround(int x, vector<int> mines)
    {
        int totalMines = 0;
        int left = x - 1;
        int right = x + 1;
        int above = x - cols;
        int below = x + cols;

        // left
        if (x % cols != 0)
        {
            if (isIntInVector(mines, left))
            {
                totalMines += 1;
            }
        }
        // right
        if (x % cols != cols - 1)
        {
            if (isIntInVector(mines, right))
            {
                totalMines += 1;
            }
        }
        // top
        if (x - cols >= 0)
        {
            if (isIntInVector(mines, above))
            {
                totalMines += 1;
            }
        }
        // bottom
        if (x + cols < cols * rows)
        {
            if (isIntInVector(mines, below))
            {
                totalMines += 1;
            }
        }

        // topleft
        if (x % cols != 0 && x - cols != 0)
        {
            int topLeft = above - 1;
            if (isIntInVector(mines, topLeft))
            {
                totalMines += 1;
            }
        }

        // topright
        if (x % cols != cols - 1 && x - cols >= 0)
        {
            int topRight = above + 1;
            if (isIntInVector(mines, topRight))
            {
                totalMines += 1;
            }
        }

        // bottomleft
        if (x + cols < cols * rows && x % cols != 0)
        {
            int bottomLeft = below - 1;
            if (isIntInVector(mines, bottomLeft))
            {
                totalMines += 1;
            }
        }

        // bottomright
        if (x + cols < cols * rows && x % cols != cols - 1)
        {
            int bottomRight = below + 1;
            if (isIntInVector(mines, bottomRight))
            {
                totalMines += 1;
            }
        }
        return totalMines;
    }

    // void openTile(int x, int y)
    // {
    //     cout << "open tile" << endl;
    //     tile &tile = tiles.at(y * cols + x);
    //     tile.setOpen(true);
    //     if( tile.getMine())
    //     {
    //        cout << "Game Over" << endl;
    //     }
    //     else if (tile.getMinesAround() == 0)
    //     {
    //         for (int i = -1; i <= 1; i++)
    //         {
    //             for (int j = -1; j <= 1; j++)
    //             {
    //                 if (i == 0 && j == 0)
    //                     continue;
    //                 int newX = x + i;
    //                 int newY = y + j;
    //                 if (newX >= 0 && newX < cols && newY >= 0 && newY < rows)
    //                 {
    //                     cout << newX << "= new x index" << endl;
    //                     cout << newY << "= new y index" << endl;
    //                     openTile(newX, newY);
    //                 }
    //             }
    //         }
    //     }
    // }

    void openTile(int x, int y) {
        tile &tile = tiles.at(y * cols + x);

        // Don't open if already opened
        if (tile.getOpen())
            return;

        if (!tile.getFlagged()) {
            tile.setOpen(true);

            cout << "Opening tile: (" << x << ", " << y << ")" << endl;

            if (tile.getMine())
            {
                gameStatus = 2;
                cout << "Game Over" << endl;
                return;
            }

            if (tile.getMinesAround() == 0)
            {
                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        if (i == 0 && j == 0)
                            continue;

                        int newX = x + i;
                        int newY = y + j;

                        if (newX >= 0 && newX < cols && newY >= 0 && newY < rows)
                        {
                            openTile(newX, newY);
                        }
                    }
                }
            }
        }
    }


    void flagTile(int x, int y)
    {
        tile &tile = tiles.at(y * cols + x);
        tile.setFlagged(!tile.getFlagged());
    }

    void loadTextures()
    {

        hiddenTexture.loadFromFile("files/images/tile_hidden.png");

        revealedTexture.loadFromFile("files/images/tile_revealed.png");

        mineTexture.loadFromFile("files/images/mine.png");

        flagTexture.loadFromFile("files/images/flag.png");

        num1Txture.loadFromFile("files/images/number_1.png");

        num2Txture.loadFromFile("files/images/number_2.png");

        num3Txture.loadFromFile("files/images/number_3.png");

        num4Txture.loadFromFile("files/images/number_4.png");

        num5Txture.loadFromFile("files/images/number_5.png");

        num6Txture.loadFromFile("files/images/number_6.png");

        num7Txture.loadFromFile("files/images/number_7.png");

        num8Txture.loadFromFile("files/images/number_8.png");
    }

    bool isWin() {
        for (int i = 0; i < tiles.size(); i++) {
            if (!tiles.at(i).getOpen() && !tiles.at(i).getMine()) {
                return false;
            }
        }
    }

    void drawGameBoard(sf::RenderWindow &gameWindow, bool isDebug)
    {
        sf::Sprite mineSprite;
        for (int i = 0; i < getTiles().size(); i++) {
            tile tile = getTiles().at(i);
            mineSprite.setPosition(tile.getX() * 32, tile.getY() * 32);
            mineSprite.setTexture(revealedTexture);
            gameWindow.draw(mineSprite);

            if (!tile.getOpen())
            {
                mineSprite.setTexture(hiddenTexture);
            }
            else if (tile.getMine())
            {
                mineSprite.setTexture(mineTexture);
            }
            else if (tile.getMinesAround() == 1)
            {
                mineSprite.setTexture(num1Txture);
            }
            else if (tile.getMinesAround() == 2)
            {
                mineSprite.setTexture(num2Txture);
            }
            else if (tile.getMinesAround() == 3)
            {
                mineSprite.setTexture(num3Txture);
            }
            else if (tile.getMinesAround() == 4)
            {
                mineSprite.setTexture(num4Txture);
            }
            else if (tile.getMinesAround() == 5)
            {
                mineSprite.setTexture(num5Txture);
            }
            else if (tile.getMinesAround() == 6)
            {
                mineSprite.setTexture(num6Txture);
            }
            else if (tile.getMinesAround() == 7)
            {
                mineSprite.setTexture(num7Txture);
            }
            else if (tile.getMinesAround() == 8)
            {
                mineSprite.setTexture(num8Txture);
            }
            else if (tile.getFlagged())
            {
                mineSprite.setTexture(flagTexture);
            }
            else
            {
                mineSprite.setTexture(revealedTexture);
            }

            gameWindow.draw(mineSprite);

            if(tile.getFlagged())
            {
                mineSprite.setTexture(flagTexture);
                gameWindow.draw(mineSprite);
            }

            if ((isDebug || gameStatus == 2) && tile.getMine())
            {
                mineSprite.setTexture(mineTexture);
                gameWindow.draw(mineSprite);

            } else if (gameStatus == 1) {

            }
        }
    }
};

#endif //BOARD_H