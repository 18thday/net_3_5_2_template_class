#include <cassert>
#include <iostream>
#include <utility>

template <typename T>
class table {
public:
    table(size_t rows, size_t cols) : ptr_table_(new T*[rows]), rows_(rows), cols_(cols) {
        for (size_t i = 0; i < rows; ++i) {
            ptr_table_[i] = new T[cols];
        }
    }

    table(const table& other) : ptr_table_(new T*[other.rows_]), rows_(other.rows_), cols_(other.cols_)  {
        for (size_t i = 0; i < rows_; ++i) {
            ptr_table_[i] = new T[cols_];
            for (size_t j = 0; j < cols_; ++j) {
                ptr_table_[i][j] = other[i][j];
            }
        }
    }

    table& operator=(const table& other) {
        if (this == &other) {
            return *this;
        }
        Clear();
        this->other(other);
    }

    ~table() {
        Clear();
    }

    T* operator[](size_t row) {
        assert(row < rows_);
        return ptr_table_[row];
    }

    const T* operator[](size_t row) const{
        assert(row < rows_);
        return ptr_table_[row];
    }

    std::pair<size_t, size_t> Size() const {
        return {rows_, cols_};
    }

private:
    T** ptr_table_ = nullptr;
    size_t rows_ = 0;
    size_t cols_ = 0;

    void Clear() {
        for (size_t i = 0; i < rows_; ++i) {
            delete[] ptr_table_[i];
        }
        delete[] ptr_table_;
    }
};

std::ostream& operator<< (std::ostream& os, std::pair<size_t, size_t> p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

int main() {
    auto test = table<int>(2, 3);
    test[0][0] = 4;
    std::cout << test[0][0] << std::endl;
    std::cout << "Size = " << test.Size();
    return 0;
}
