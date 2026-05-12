#include <iostream>
#include <tuple>
#include <initializer_list>
#include <stdexcept>
#include <cmath>


struct vector2
{
    float x;
    float y;

    double length()
    {
        return std::sqrt(x * x + y * y);
    }

    double distance(vector2 other)
    {
        return std::sqrt(
            (x - other.x) * (x - other.x) +
            (y - other.y) * (y - other.y)
        );
    }

    double dot(vector2 other)
    {
        return x * other.x + y * other.y;
    }

    vector2 operator+(const vector2& other)
    {
        return {
            x + other.x,
            y + other.y,
        };
    }
};

struct vector3
{
    float x;
    float y;
    float z;

    double length()
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    double distance(vector3 other)
    {
        return std::sqrt(
            (x - other.x) * (x - other.x) +
            (y - other.y) * (y - other.y) +
            (z - other.z) * (z - other.z)
        );
    }

    double dot(vector3 other)
    {
        return x * other.x + y * other.y + z * other.z;
    }

    vector3 operator+(const vector3& other)
    {
        return {
            x + other.x,
            y + other.y,
            z + other.z
        };
    }
};

struct matrix
{
    int rows;
    int cols;

    float** data;

    std::tuple<int, int> size;

    // Constructor
    matrix(int rows, int cols)
        : rows(rows), cols(cols), size(rows, cols)
    {
        data = new float* [rows];

        for (int i = 0; i < rows; i++)
        {
            data[i] = new float[cols];

            // Initialize to 0
            for (int j = 0; j < cols; j++)
            {
                data[i][j] = 0.0f;
            }
        }
    }

    void set_matrix(std::initializer_list<std::initializer_list<float>> values)
    {
        if (values.size() > rows)
        {
            throw std::invalid_argument(
                "Too many rows for matrix"
            );
        }

        int row = 0;

        for (const auto& current_row : values)
        {
            //std::cout << row << "\n";
            set_row(row, current_row);
            row++;
        }
    }

    // Set an entire row
    void set_row(int row, std::initializer_list<float> items)
    {
        if (row < 0 || row >= rows)
        {
            throw std::invalid_argument("Row out of range");
        }

        if (items.size() > cols)
        {
            throw std::invalid_argument("Too many columns");
        }

        int col = 0;

        for (float val : items)
        {
            data[row][col] = val;
            col++;
        }
    }
    // Set an entire col
    void set_col(int col, std::initializer_list<float> items)
    {
        int const length = items.size();

        if (col < 0 || col >= cols)
        {
            throw std::invalid_argument("Col out of range");
        }

        if (length > rows)
        {
            throw std::invalid_argument(
                "Too many items for col"
            );
        }

        int i = 0;

        for (float val : items)
        {
            data[i++][col] = val;
        }
    }


    // Set a single item
    void set_item(int row, int col, float value)
    {
        if (row < 0 || row >= rows)
        {
            throw std::invalid_argument("Row out of range");
        }

        if (col < 0 || col >= cols)
        {
            throw std::invalid_argument("Column out of range");
        }

        data[row][col] = value;
    }

    // Get a single item
    float get_item(int row, int col) const //identify it is a constant
    {
        if (row < 0 || row >= rows)
        {
            throw std::invalid_argument("Row out of range");
        }

        if (col < 0 || col >= cols)
        {
            throw std::invalid_argument("Column out of range");
        }

        return data[row][col];
    }

    // Print matrix
    void print(std::string end = "") const
    {
        std::cout << end;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << data[i][j] << " ";
            }

            std::cout << std::endl;
        }
    }

    matrix operator+(const matrix& other)
    {
        if (other.size != size)
        {
            throw std::exception("Matrix sizes are not equal");
        }

        matrix final(rows, cols);
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                float sum = data[row][col] + other.data[row][col];
                final.set_item(row, col, sum);
            }
        }
        return final;

    }

    matrix operator*(const matrix& other)
    {
        if (cols != other.rows)
        {
            throw std::invalid_argument("Matrix cannot be multiplied");
        }

        matrix result(rows, other.cols);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < other.cols; j++)
            {
                float sum = 0.0f;

                for (int k = 0; k < cols; k++)
                {
                    sum += data[i][k] * other.data[k][j];
                }

                result.set_item(i, j, sum);
            }
        }

        return result;
    }

    float determinant() const
    {
        if (rows != cols)
            throw std::invalid_argument("Matrix must be square");

        if (rows == 2)
        {
            return data[0][0] * data[1][1]
                - data[0][1] * data[1][0];
        }

        if (rows == 3)
        {
            return
                data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
                - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0])
                + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
        }

        throw std::invalid_argument("Only 2x2 and 3x3 matrices supported");
    }

    matrix inverse() const
    {
        if (rows != cols)
            throw std::invalid_argument("Matrix must be square");

        matrix result(rows, cols);

        if (rows == 2)
        {
            float det = determinant();

            if (det == 0)
                throw std::invalid_argument("Matrix is not invertible");

            result.data[0][0] = data[1][1];
            result.data[0][1] = -data[0][1];
            result.data[1][0] = -data[1][0];
            result.data[1][1] = data[0][0];

            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    result.data[i][j] /= det;

            return result;
        }

        if (rows == 3)
        {
            float det = determinant();

            if (det == 0)
                throw std::invalid_argument("Matrix is not invertible");

            // Cofactor matrix
            result.data[0][0] = (data[1][1] * data[2][2] - data[1][2] * data[2][1]);
            result.data[0][1] = -(data[0][1] * data[2][2] - data[0][2] * data[2][1]);
            result.data[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]);

            result.data[1][0] = -(data[1][0] * data[2][2] - data[1][2] * data[2][0]);
            result.data[1][1] = (data[0][0] * data[2][2] - data[0][2] * data[2][0]);
            result.data[1][2] = -(data[0][0] * data[1][2] - data[0][2] * data[1][0]);

            result.data[2][0] = (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
            result.data[2][1] = -(data[0][0] * data[2][1] - data[0][1] * data[2][0]);
            result.data[2][2] = (data[0][0] * data[1][1] - data[0][1] * data[1][0]);

            // divide by determinant
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    result.data[i][j] /= det;

            return result;
        }

        throw std::invalid_argument("Only 2x2 and 3x3 matrices supported");
    }

    // Destructor
    ~matrix()
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] data[i];
        }

        delete[] data;
    }
};
