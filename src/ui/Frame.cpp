#include "ui/Frame.h"

//为什么setposition是左下角的点？还有这个setsize是什么勾八情况？？总之是能跑了
//设置边框ui位置
Frame::Frame(sf::Vector2f lefttop,sf::Vector2f rightbottom,int width,sf::Color color_in,sf::Color color_out)
{
    frame_in_.setPosition(lefttop);
    frame_in_.setSize({rightbottom.x-lefttop.x,rightbottom.y-lefttop.y});
    frame_in_.setFillColor(color_in);
    frame_out_.setPosition({lefttop.x-width,lefttop.y-width});
    frame_out_.setSize({rightbottom.x-lefttop.x+(2*width),rightbottom.y-lefttop.y+(2*width)});
    frame_out_.setFillColor(color_out);
}

sf::FloatRect Frame::getGlobalBounds()
{
    return frame_in_.getGlobalBounds();
}

void Frame::drawwindow(sf::RenderWindow& window)
{
    window.draw(frame_out_);
    window.draw(frame_in_);
}