
struct Point {
    int vertices[4];
    Point* upper = nullptr;
    Point* bottom = nullptr;
    Point* left = nullptr;
    Point* right = nullptr;
    bool upper_connection = false;
    bool bottom_connection = false;
    bool left_connection = false;
    bool right_connection = false;
    bool left_right_connection = false;
    bool right_left_connection = false;
};