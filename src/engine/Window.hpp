#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {
  private:
    int width_;
    int height_;
    double distance_;

  public:
    Window();
    Window(int width, int height, double distance);

    int getWidth();
    int getHeight();
    double getDistance();

    void print();
};

#endif