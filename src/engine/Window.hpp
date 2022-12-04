#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {
  private:
    int width_;
    int height_;
    float distance_;

  public:
    Window();
    Window(int width, int height, float distance);

    int getWidth();
    int getHeight();
    float getDistance();

    void print();
};

#endif