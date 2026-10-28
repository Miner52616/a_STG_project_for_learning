#include "ui/KeyBoard.h"
#include "ui/Button.h"

KeyBoard::KeyBoard(const sf::Font &font):
    font_(font)
{
    input_="";

    focus_.emplace_back(1);
    focus_.emplace_back(1);

    

    key_net_.reserve(row);
    for(int i=1;i<=row;i++)
    {
        std::vector<Button> key_row;
        key_row.reserve(column);
        for(int j=1;j<=column;j++)
        {
            key_row.emplace_back(font_);
        }
        key_net_.emplace_back(std::move(key_row));
    }

    for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=column;j++)
        {
            key_net_[i-1][j-1].setButtonSize(35);
        }
    }

    //注意：这里不能声明名为 origin_net_ 的局部变量，否则会遮蔽同名成员，
    //导致 addString() 读到的成员数组始终是空字符串
    const std::string key_layout[row][column]=
    {
        {"A","B","C","D","E","F","G","H","I","J","K","L","M"},
        {"N","O","P","Q","R","S","T","U","V","W","X","Y","Z"},
        {"a","b","c","d","e","f","g","h","i","j","k","l","m"},
        {"n","o","p","q","r","s","t","u","v","w","x","y","z"},
        {"0","1","2","3","4","5","6","7","8","9","+","-","="},
        {".",",","!","?","@",":",";","[","]","(",")","_","/"},
        {"{","}","|","~","^","#","$","%","&","*","SP","BS","END"}
    };

    for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=column;j++)
        {
            origin_net_[i-1][j-1]=key_layout[i-1][j-1];
            key_net_[i-1][j-1].setButtonText(origin_net_[i-1][j-1]);
            key_net_[i-1][j-1].setButtonShake(0,0);
        }
    }
}

void KeyBoard::update()
{
    for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=column;j++)
        {
            key_net_[i-1][j-1].setButtonFocused(not_befocused);
        }
    }

    key_net_[focus_[0]-1][focus_[1]-1].setButtonFocused(befocused);
}

void KeyBoard::render(sf::RenderWindow& window)
{
    for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=column;j++)
        {
            key_net_[i-1][j-1].render(window);
        }
    }
}

void KeyBoard::setPosition(sf::Vector2f position)
{
    position_=position;
    for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=column;j++)
        {
            key_net_[i-1][j-1].setButtonPosition({position.x+(j-1)*40,position.y+(i-1)*40});
            key_net_[i-1][j-1].setButtonShake(0,0);
            key_net_[i-1][j-1].update();
        }
    }
}

std::vector<int> KeyBoard::getFocus()
{
    return focus_;
}

void KeyBoard::setFocus(const std::vector<int>& focus)
{
    focus_[0]=focus[0];
    focus_[1]=focus[1];
}

std::string KeyBoard::getString()
{
    return input_;
}

void KeyBoard::addString()
{
    bool special_key=(focus_[0]==7)&&(focus_[1]>=11);
    if(!special_key)
    {
        if(input_.size()<static_cast<std::size_t>(max_input_length))
        {
            input_=input_+origin_net_[focus_[0]-1][focus_[1]-1];
        }
        return;
    }

    switch (focus_[1])
    {
    case 11:
        {
            if(input_.size()<static_cast<std::size_t>(max_input_length))
            {
                input_=input_+" ";
            }
            break;
        }

    case 12:
        {
            if(!input_.empty())
            {
                input_.pop_back();
            }
            break;
        }

    case 13:
        break;

    default:
        break;
    }
}

void KeyBoard::setString(std::string string)
{
    input_=string;
}