#include "field.h"

void Field::GenerateField(int x) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_pos(0,8);
    std::uniform_int_distribution<> dist_times(5,8);
    std::uniform_int_distribution<> dist_swap(1,3);
    int k = 1;
    int count = 9;
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            field_[i][j] = k;
            k++;
            if (k >= 10) k = 1;
        }

        k += 3;
        if (k >= 10) k = 1;
        count--;
        if (count == 6) k = 2;
        if (count == 3) k = 3;
    }

    int swap_clos_times = dist_times(gen);
    while (swap_clos_times > 0) {
        SwapCols(dist_swap(gen));
        SwapRows(dist_swap(gen));
        swap_clos_times--;
    }

    int swap_bloc_times = dist_times(gen);
    while (swap_bloc_times > 0) {
        SwapHorizBlocks(dist_swap(gen));
        SwapVertBlocks(dist_swap(gen));
        swap_bloc_times--;
    }

    while (x > 0) {
        int i = dist_pos(gen);
        int j = dist_pos(gen);
        if (field_[i][j] == 0) {
            continue;
        }
        field_[i][j] = 0;
        x--;
    }
}

void Field::SwapCols (int t) {
    if (t == 1) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[i][0], field_[i][2]);
        }
    } else if (t == 2) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[i][3], field_[i][5]);
        }
    } else if (t == 3) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[i][6], field_[i][8]);
        }
    }
}

void Field::SwapRows (int t) {
    if (t == 1) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[0][i], field_[2][i]);
        }
    } else if (t == 2) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[3][i], field_[5][i]);
        }
    } else if (t == 3) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[6][i], field_[8][i]);
        }
    }
}

void Field::SwapHorizBlocks (int t) {
    if (t == 1) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[0][i], field_[6][i]);
            std::swap(field_[1][i], field_[7][i]);
            std::swap(field_[2][i], field_[8][i]);
        }
    } else if (t == 2) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[0][i], field_[3][i]);
            std::swap(field_[1][i], field_[4][i]);
            std::swap(field_[2][i], field_[5][i]);
        }
    } else if (t == 3) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[3][i], field_[6][i]);
            std::swap(field_[4][i], field_[7][i]);
            std::swap(field_[5][i], field_[8][i]);
        }
    }
}

void Field::SwapVertBlocks (int t) {
    if (t == 1) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[i][0], field_[i][6]);
            std::swap(field_[i][1], field_[i][7]);
            std::swap(field_[i][2], field_[i][8]);
        }
    } else if (t == 2) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[i][0], field_[i][3]);
            std::swap(field_[i][1], field_[i][4]);
            std::swap(field_[i][2], field_[i][5]);
        }
    } else if (t == 3) {
        for (size_t i = 0; i < 9; ++i) {
            std::swap(field_[i][3], field_[i][6]);
            std::swap(field_[i][4], field_[i][7]);
            std::swap(field_[i][5], field_[i][8]);
        }
    }
}

bool Field::CheckLine (int i, int j, int val) const {
    for (int k = 0; k < 9; k++) {
        if (i == k || field_[k][j] == 0) continue;
        if (val == field_[k][j]) {
            return true;
        }

    }

    for (int l = 0; l < 9; l++) {
        if (l == j || field_[i][l] == 0) continue;
        if (val == field_[i][l]) {
            return true;
        }
    }
    return false;
}

bool Field::CheckCorrectSquare(int i, int j, int val) const {
    if ((i == 0 || i == 1 || i == 2) && (j == 0 || j == 1 || j == 2)) {
        for (size_t k = 0; k < 3; ++k) {
            for (size_t l = 0; l < 3; ++l) {
                if((k == static_cast<size_t>(i) && l == static_cast<size_t>(j)) || field_[k][l] == 0) continue;
                if (val == field_[k][l] && val != 0) {
                    return true;
                }
            }
        }
    } else if ((i == 3 || i == 4 || i == 5) && (j == 0 || j == 1 || j == 2)) {
        for (size_t k = 3; k < 6; ++k) {
            for (size_t l = 0; l < 3; ++l) {
                if((k == static_cast<size_t>(i) && l == static_cast<size_t>(j)) || field_[k][l] == 0) continue;
                if (val == field_[k][l] && val != 0) {
                    return true;
                }
            }
        }
    } else if ((i == 6 || i == 7 || i == 8) && (j == 0 || j == 1 || j == 2)) {
        for (size_t k = 6; k < 9; ++k) {
            for (size_t l = 0; l < 3; ++l) {
                if((k == static_cast<size_t>(i) && l == static_cast<size_t>(j)) || field_[k][l] == 0) continue;
                if (val == field_[k][l] && val != 0) {
                    return true;
                }
            }
        }
    } else if ((i == 0 || i == 1 || i == 2) && (j == 3 || j == 4 || j == 5)) {
        for (size_t k = 0; k < 3; ++k) {
            for (size_t l = 3; l < 6; ++l) {
                if((k == static_cast<size_t>(i) && l == static_cast<size_t>(j)) || field_[k][l] == 0) continue;
                if (val == field_[k][l] && val != 0) {
                    return true;
                }
            }
        }
    } else if ((i == 0 || i == 1 || i == 2) && (j == 6 || j == 7 || j == 8)) {
        for (size_t k = 0; k < 3; ++k) {
            for (size_t l = 6; l < 9; ++l) {
                if((k == static_cast<size_t>(i) && l == static_cast<size_t>(j)) || field_[k][l] == 0) continue;
                if (val == field_[k][l] && val != 0) {
                    return true;
                }
            }
        }
    } else if ((i == 3 || i == 4 || i == 5) && (j == 3|| j == 4 || j == 5)) {
        for (size_t k = 3; k < 6; ++k) {
            for (size_t l = 3; l < 6; ++l) {
                if((k == static_cast<size_t>(i) && l == static_cast<size_t>(j)) || field_[k][l] == 0) continue;
                if (val == field_[k][l] && val != 0) {
                    return true;
                }
            }
        }
    } else if ((i == 6 || i == 7 || i == 8) && (j == 6 || j == 7 || j == 8)) {
        for (size_t k = 6; k < 9; ++k) {
            for (size_t l = 6; l < 9; ++l) {
                if((k == static_cast<size_t>(i) && l == static_cast<size_t>(j)) || field_[k][l] == 0) continue;
                if (val == field_[k][l] && val != 0) {
                    return true;
                }
            }
        }
    } else if ((i == 3 || i == 4 || i == 5) && (j == 6 || j == 7 || j == 8)) {
        for (size_t k = 3; k < 6; ++k) {
            for (size_t l = 6; l < 9; ++l) {
                if((k == static_cast<size_t>(i) && l == static_cast<size_t>(j)) || field_[k][l] == 0) continue;
                if (val == field_[k][l] && val != 0) {
                    return true;
                }
            }
        }
    } else if ((i == 6 || i == 7 || i == 8) && (j == 3 || j == 4 || j == 5)) {
        for (size_t k = 6; k < 9; ++k) {
            for (size_t l = 3; l < 6; ++l) {
                if((k == static_cast<size_t>(i) && l == static_cast<size_t>(j)) || field_[k][l] == 0) continue;
                if (val == field_[k][l] && val != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Field::SetNum (int i, int j, int val) {
    field_[i][j] = val;
}

std::vector<std::vector<int>> Field::GetField () const {
    return field_;
};
