#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <random>
#include <algorithm>

class Field
{
public:
    explicit Field() = default;
    void GenerateField(int x);
    std::vector<std::vector<int>> GetField () {
        return field_;
    };
    void ResetField_();
    bool CheckCorrectSquare(int i, int j, int val) const;
    void SetNum (int i, int j, int val);
    bool CheckLine (int i, int j, int val) const;
    void SwapCols (int t);
    void SwapRows (int t);
private:
    std::vector<std::vector<int>> field_ {9, std::vector<int>(9)};
};

#endif // FIELD_H
