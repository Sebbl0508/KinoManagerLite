#include <vector>
#include <random>
#include <ctime>
#include <functional>

class Kinosaal
{
public:
    Kinosaal(int inRows, int inCols)
    {
        std::default_random_engine gen;
        std::uniform_int_distribution<int> distribution(0, 1);

        auto randBool = std::bind(distribution, gen);

        this->rows = inRows;
        this->cols = inCols;

        for(int i = 0; i < inRows; i++)
        {
            std::vector<bool> tmpArr;
            tmpArr.reserve(inCols);
            for(int j = 0; j < inCols; j++)
            {
                tmpArr.push_back(false);
            }
            this->saalGrid.push_back(tmpArr);
        }
        // std::cout << "Done initializing" << std::endl;
    }
    bool reservSeat(int x, int y)
    {
        if(this->saalGrid[x][y])
        {
            return false;
        } else if (!this->saalGrid[x][y]) {
            this->saalGrid[x][y] = !this->saalGrid[x][y];
            return true;
        }
        return false;
    }
    int getRows()
    {
        return this->rows;
    }

    int getCols()
    {
        return this->cols;
    }


    void printGrid()
    {
//        for(int k = 0; k < this->cols; k++)
//        {
//            std::cout << k << " ";
//        }
        for(int i = 0; i < this->rows; i++)
        {
//            if(i > 0)
//            {
//                std::cout << i << " ";
//            }
            for(int j = 0; j < this->cols; j++)
            {
                if(!this->saalGrid[i][j])
                {
                    std::cout << "O" << " ";
                } else if(saalGrid[i][j]) {
                    std::cout << "X" << " ";
                }
            }
            std::cout << std::endl;
        }
    }
private:
    int rows;
    int cols;
    std::vector<std::vector<bool>> saalGrid;
};