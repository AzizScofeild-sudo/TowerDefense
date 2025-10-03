#ifndef __WINDOW__
#define __WINDOW__

#include <string>
#include <SFML/Graphics.hpp>  

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();


    
    void start();

    void show();
    void close();
    bool isOpen() const;

    int getWidth() const;
    int getHeight() const;
    std::string getTitle() const;

private:
    int m_width;
    int m_height;
    std::string m_title;
    bool m_isOpen;
};

#endif  __WINDOW__

