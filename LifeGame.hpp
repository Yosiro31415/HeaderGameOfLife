#ifndef _LIFEGAME_
#define _LIFEGAME_

#include <vector>
#include <iostream>

namespace LIFEGAME {
struct CellLifeGame {
    bool isAlive = false;
};

class LifeGame {
    int height;
    int width;

protected:
    std::vector<std::vector<CellLifeGame>> tile = {}; //縦横の予定
    int checkCell(int in_y, int in_x, std::vector<std::vector<CellLifeGame>>* oldTile);

public:
    LifeGame(std::vector<std::vector<CellLifeGame>> in_tile);
    LifeGame(std::vector<std::vector<int>> in_tile);
    ~LifeGame();
    int update();
    std::vector<std::vector<int>> output();

    int showOutputCL(LifeGame* LG);
};

int showOutput(LifeGame* LG) {
    system("cls");
    std::vector<std::vector<int>> OP = LG->output();
    for (int i = 0; i < OP.size(); i++) {
        for (int j = 0; j < OP.at(0).size(); j++) {
            if (!OP.at(i).at(j)) {
                std::cout << "□ ";
            } else {
                std::cout << "■ ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

LifeGame::LifeGame(std::vector<std::vector<CellLifeGame>> in_tile) {
    tile = in_tile;
    width = in_tile.at(0).size();
    height = in_tile.size();
};

LifeGame::LifeGame(std::vector<std::vector<int>> in_tile) {
    height = in_tile.size();
    width = in_tile.at(0).size();
    for (int i = 0; i < height; i++) {
        std::vector<CellLifeGame> line = {};
        for (int j = 0; j < width; j++) {
            CellLifeGame cell;
            if (in_tile.at(i).at(j) > 0)
                cell.isAlive = true;
            line.push_back(cell);
        }
        tile.push_back(line);
    }
};

LifeGame::~LifeGame(){

};
int LifeGame::update() {

    std::vector<std::vector<CellLifeGame>> oldTile;
    oldTile = tile;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            checkCell(i, j, &oldTile);
        }
    }
    return 0;
};

int LifeGame::checkCell(int in_y, int in_x, std::vector<std::vector<CellLifeGame>>* oldTile) {

    int head = in_y + 1;
    int foot = in_y - 1;
    int right = in_x + 1;
    int left = in_x - 1;

    if (in_x > width || in_x < 0) {
        return 1;
    }
    if (in_y > height || in_y < 0) {
        return 1;
    }

    int numLivCel = 0;
    if ((head < height) && (right < width) && oldTile->at(head).at(right).isAlive)
        numLivCel++;
    if ((head < height) && oldTile->at(head).at(in_x).isAlive)
        numLivCel++;
    if ((head < height) && (left > 0) && oldTile->at(head).at(left).isAlive)
        numLivCel++;
    if ((left > 0) && oldTile->at(in_y).at(left).isAlive)
        numLivCel++;
    if ((right < width) && oldTile->at(in_y).at(right).isAlive)
        numLivCel++;
    if ((right < width) && (foot > 0) && oldTile->at(foot).at(right).isAlive)
        numLivCel++;
    if ((foot > 0) && oldTile->at(foot).at(in_x).isAlive)
        numLivCel++;
    if ((foot > 0) && (left > 0) && oldTile->at(foot).at(left).isAlive)
        numLivCel++;
    if (oldTile->at(in_y).at(in_x).isAlive) {
        if (numLivCel == 2 || numLivCel == 3) {
            tile.at(in_y).at(in_x).isAlive = true;
        } else
            tile.at(in_y).at(in_x).isAlive = false;
    } else {
        if (numLivCel == 3) {
            tile.at(in_y).at(in_x).isAlive = true;

        } else
            tile.at(in_y).at(in_x).isAlive = false;
    }
    return 0;
};
std::vector<std::vector<int>> LifeGame::output() {
    std::vector<std::vector<int>> OP;
    for (int i = 0; i < height; i++) {
        std::vector<int> line = {};
        for (int j = 0; j < width; j++) {
            CellLifeGame cell;
            if (tile.at(i).at(j).isAlive)
                cell.isAlive = true;
            line.push_back(cell.isAlive);
        }
        OP.push_back(line);
    }
    return OP;
};
} // namespace LIFEGAME
#endif
