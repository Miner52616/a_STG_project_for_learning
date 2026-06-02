#include "overlays/overlays/texturecurtains/StarCurtain.h"
#include "mathematics/mathematics.h"
#include <iostream>

StarConfig::StarConfig():
    clock_(0)
{
    clock_.reset();
}

StarCurtain::StarCurtain(sf::Texture& texture):
    TextureCurtain(texture),
    mode_(1),
    num_x_(0),num_y_(0),
    start_position_({0,0}),target_position_({0,0}),target_angle_(0)
{
    ;
}

std::vector<sf::Vertex> getStarTriangleVertex(sf::Vector2f position,float angle,float r)
{
    std::vector<sf::Vertex> vertex_list;
    sf::Vector2f direction={0,-1};
    direction=roundwithCenter({0,0},direction,angle);

    for(int i=1;i<=5;i++)
    {
        sf::Vector2f point1=position;
        sf::Vector2f point2=position+direction*r;
        sf::Vector2f point3=position+(float)0.5*roundwithCenter({0,0},direction,36)*r;
        sf::Vector2f point4=position+(float)0.5*roundwithCenter({0,0},direction,-36)*r;

        sf::Vertex vertex1;
        vertex1.position=point1;
        vertex1.texCoords=point1;
        vertex1.color=sf::Color::White;

        sf::Vertex vertex2;
        vertex2.position=point2;
        vertex2.texCoords=point2;
        vertex2.color=sf::Color::White;

        sf::Vertex vertex3;
        vertex3.position=point3;
        vertex3.texCoords=point3;
        vertex3.color=sf::Color::White;

        sf::Vertex vertex4;
        vertex4.position=point1;
        vertex4.texCoords=point1;
        vertex4.color=sf::Color::White;

        sf::Vertex vertex5;
        vertex5.position=point2;
        vertex5.texCoords=point2;
        vertex5.color=sf::Color::White;

        sf::Vertex vertex6;
        vertex6.position=point4;
        vertex6.texCoords=point4;
        vertex6.color=sf::Color::White;

        vertex_list.emplace_back(vertex1);
        vertex_list.emplace_back(vertex2);
        vertex_list.emplace_back(vertex3);
        vertex_list.emplace_back(vertex4);
        vertex_list.emplace_back(vertex5);
        vertex_list.emplace_back(vertex6);

        direction=roundwithCenter({0,0},direction,72);
    }

    return vertex_list;
}

void StarCurtain::setNum(int num_x,int num_y)
{
    num_x_=num_x;
    num_y_=num_y;
}

//注意，由于需要根据右下角星星的移动轨迹推算其它位置星星的移动轨迹，务必在设置轨迹之前设置好星星的x，y数量！
void StarCurtain::setStart_Target(sf::Vector2f start_position,sf::Vector2f target_position,float target_angle)
{
    start_position_=start_position;
    target_position_=target_position;

    float x_ref=1280-0.5*((float)1280/num_x_);
    float y_ref=960-0.5*((float)960/num_y_);
    sf::Vector2f start_translation=start_position_-sf::Vector2f{x_ref,y_ref};
    sf::Vector2f target_translation=target_position_-sf::Vector2f{x_ref,y_ref};;

    //x额外+10个，这样可以不会出现“只是星星铺满了屏幕”的观感
    //+10意味着左右各+5星星，这样斜向飞出时不会左上/右上有地方没被覆盖到
    for(int i=1;i<=num_x_+1+10;i++)
    {
        std::vector<Star> store;
        for(int j=1;j<=num_y_;j++)
        {
            Star star;
            float x=(j%2)*(0.5*((float)1280/num_x_))+((float)(i-1-10/2))*((float)1280/num_x_);
            float y=0.5*((float)960/num_y_)+((float)(j-1))*((float)960/num_y_);
            star.setPosition(sf::Vector2f{x,y}+start_translation);
            star.getConfig()->target_position_=sf::Vector2f{x,y}+target_translation;
            star.getConfig()->target_angle_=target_angle;
            switch (mode_)
            {
            case 1:
                {   
                    star.getConfig()->clock_.set_target((j)*4+(num_x_-i)*7);
                    break;
                }

            case 2:
                {   
                    star.getConfig()->clock_.set_target((num_y_-j)*4+(num_x_-i)*7);
                    break;
                }
            
            default:
                break;
            }

            store.emplace_back(star);
        }

        star_matrix_.emplace_back(store);
    }
}

void StarCurtain::update()
{
    if(enable_&&(!finish_))
    {
        vertices_.clear();

        std::vector<sf::Vertex> vertex_list;

        for(auto line=star_matrix_.begin();line!=star_matrix_.end();++line)
        {
            for(auto star=(*line).begin();star!=(*line).end();++star)
            {
                star->update();
                std::vector<sf::Vertex> star_vertex=getStarTriangleVertex(star->getPosition(),star->getAngle(),star->getR());
                for(int i=1;i<=star_vertex.size();i++)
                {
                    vertex_list.emplace_back(star_vertex[i-1]);
                }
            }
        }


        //std::vector<sf::Vertex> vertex_list=getStarTriangleVertex({150,150},100);
        //std::cout<<vertex_list.size()<<std::endl;
        for(auto it=vertex_list.begin();it!=vertex_list.end();++it)
        {
            //std::cout<<"1"<<std::endl;
            vertices_.append(*it);
        }

        sf::Vector2f current=(star_matrix_.begin())->begin()->getPosition();
        sf::Vector2f target=(star_matrix_.begin())->begin()->getConfig()->target_position_;
        bool finish=(target.x-current.x<=0.1)&&(target.y-current.y<=0.1);
        if(finish)
        {
            finish_=true;
        }
    }
}

//************************************************************** */

StarCurtain2::StarCurtain2(sf::Texture& texture):
    TextureCurtain(texture)
{
    ;
}

void StarCurtain2::add_star(Star& star)
{
    star_list_.emplace_back(star);
}

void StarCurtain2::update()
{
    if(enable_&&(!finish_))
    {
        vertices_.clear();

        std::vector<sf::Vertex> vertex_list;

        //std::cout<<star_list_.size()<<std::endl;
        for(auto star=star_list_.begin();star!=star_list_.end();++star)
        {
            star->update();
            std::vector<sf::Vertex> star_vertex=getStarTriangleVertex(star->getPosition(),star->getAngle(),star->getR());
            for(int i=1;i<=star_vertex.size();i++)
            {
                vertex_list.emplace_back(star_vertex[i-1]);
            }
        }

        for(auto it=vertex_list.begin();it!=vertex_list.end();++it)
        {
            //std::cout<<"1"<<std::endl;
            vertices_.append(*it);
        }

        if(abs(star_list_.begin()->getConfig()->target_r_-star_list_.begin()->getR())<=0.1)
        {
            finish_=true;
        }
    }
}

//********************************************************************** */

StarConfig* Star::getConfig()
{
    return &config_;
}

void Star::setPosition(sf::Vector2f position)
{
    position_=position;
}

void Star::setAngle(float angle)
{
    angle_=angle;
}

void Star::setR(float r)
{
    r_=r;
}

sf::Vector2f Star::getPosition()
{
    return position_;
}

float Star::getAngle()
{
    return angle_;
}

float Star::getR()
{
    return r_;
}

void Star::update()
{
    if(config_.clock_.get_condition())
    {
        setPosition(getPosition()+(float)0.05*(config_.target_position_-getPosition()));
        setAngle(getAngle()+0.05*(config_.target_angle_-getAngle()));
        setR(getR()+0.05*(config_.target_r_-getR()));
        //std::cout<<getPosition().x<<" "<<getPosition().y<<std::endl;
        //std::cout<<getR()<<std::endl;
        //std::cout<<getAngle()<<std::endl;
    }
    config_.clock_.count();
}