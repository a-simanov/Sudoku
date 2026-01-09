#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <random>
#include <algorithm>

inline const int NUMBER_CELLS_IN_LINE = 9;

class Field
{
public:
    explicit Field() = default;
    void GenerateField(int x);
    std::vector<std::vector<int>> GetField () const;
    bool CheckCorrectSquare(int i, int j, int val) const;
    bool CheckMiniSquare(size_t start_row, size_t finish_row, size_t start_col, size_t finish_col) const;
    void SetNum (int i, int j, int val);
    bool CheckLine (int i, int j, int val) const;

private:
    void SwapCols (int t);
    void SwapRows (int t);
    void SwapVertBlocks (int t);
    void SwapHorizBlocks (int t);
    std::vector<std::vector<int>> field_ {9, std::vector<int>(9)};
};

#endif // FIELD_H
