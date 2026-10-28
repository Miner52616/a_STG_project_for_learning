#include <filesystem>
#include <fstream>
#include "states/ReplayState.h"
#include "core/Application.h"
#include "states/GameState.h"
#include "mathematics/mathematics.h"

ReplayState::ReplayState(Application &app,GameState* game):
    ButtonState(app,ReplayButtonNum),
    game_(game),
    keyboard_(app.assets_resource_.mainFont_),
    target_position_({100,1200}),current_position_({100,1200})
    //save_mode_(save_mode)
{
    if(game!=nullptr)
    {
        save_mode_=true;
    }

    keyboard_.setPosition(current_position_);

    button_target_position_.resize(ReplayButtonNum);

    load_replay();
    for(int i=1;i<=ReplayButtonNum;i++)
    {
        buttonlist_[i-1].setButtonPosition({100,(float)70+((float)i*(float)25)});
        buttonlist_[i-1].setButtonShake(0,0);
    }
}

void ReplayState::load_replay()
{
    std::string file_head="replay/replay_";
    std::string file_end=".rep";

    for(int i=1;i<=ReplayButtonNum;i++)
    {
        buttonlist_[i-1].setButtonText(std::to_string(i)+"  --------------------");
        //buttonlist_[i-1].setButtonPosition({100,(float)70+((float)i*(float)25)});
        //button_target_position_[i-1]={100,(float)70+((float)i*(float)25)};
        buttonlist_[i-1].setButtonSize(25);
        //buttonlist_[i-1].setButtonShake(5,15);
        std::string file_name=file_head+std::to_string(i)+file_end;

        
        if(std::filesystem::exists(file_name))
        {
            std::ifstream file(file_name,std::ios::binary);
            if(!file)
            {
                std::cout<<"Fail to Open Replay File "<<i<<std::endl;
                break;
            }

            char lable[5];
            file.read(lable,sizeof(lable));

            char wanted_lable[]={'5','2','6','1','6'};

            if
            (
                lable[0]!=wanted_lable[0]||
                lable[1]!=wanted_lable[1]||
                lable[2]!=wanted_lable[2]||
                lable[3]!=wanted_lable[3]||
                lable[4]!=wanted_lable[4]
            )
            {
                std::cout<<"Replay "<<i<<" Lable Wrong!!!"<<std::endl;
                continue;;
            }

            char replay_name[10];
            file.read(replay_name,10);

            std::string replay_name_string(replay_name,10);

            buttonlist_[i-1].setButtonText(std::to_string(i)+"  "+replay_name_string);
        }
    }
}

void ReplayState::update()
{
    ButtonState::update();
    current_position_=current_position_+0.1f*(target_position_-current_position_);
    keyboard_.setPosition(current_position_);
    keyboard_.update();

    switch(phase_)
    {
        
    case 1:
        {
            for(int i=1;i<=ReplayButtonNum;i++)
            {
                button_target_position_[i-1]={100,(float)70+((float)i*(float)25)};
            }
            target_position_={100,1200};
            break;
        }
            

    case 2:
        {
            button_target_position_[focus_-1]={500,560};
            target_position_={500,600};
            buttonlist_[focus_-1].setButtonText(std::to_string(focus_)+"  "+keyboard_.getString());
            break;
        }
    default:
        {
            break;
        }
    }

    for(int i=1;i<=ReplayButtonNum;i++)
    {
        buttonlist_[i-1].setButtonPosition(buttonlist_[i-1].getButtonPosition()+0.1f*(button_target_position_[i-1]-buttonlist_[i-1].getButtonPosition()));
        buttonlist_[i-1].setButtonShake(0,0);
    }
}

void ReplayState::render(sf::RenderWindow& window)
{
    ButtonState::render(window);
    keyboard_.render(window);
}

void ReplayState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    switch (phase_)
    {
    case 1:
        {
            if(key.code==sf::Keyboard::Key::Down)
            {
                do
                {
                        focus_=(focus_%ReplayButtonNum)+1;
                }while(buttonlist_[focus_-1].getButtonLocked()==locked);
                buttonlist_[focus_-1].shake();
            }

            if(key.code==sf::Keyboard::Key::Up)
            {
                do
                {
                    focus_--;
                    if(focus_<1)
                    {
                        focus_=focus_+ReplayButtonNum;
                    }
                }while(buttonlist_[focus_-1].getButtonLocked()==locked);
                buttonlist_[focus_-1].shake();
            }

            if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
            {
                app_.stack_.popRequest();
            }

            if(key.code==sf::Keyboard::Key::Z)
            {
                if(save_mode_)
                {
                    phase_=2;
                }
                else
                {
                    std::string path="replay/replay_"+std::to_string(focus_)+".rep";
                    if(std::filesystem::exists(path))
                    {
                        app_.stack_.pushRequest(std::make_unique<GameState>(app_,path));
                    }
                }
            }
            break;
        }
    
    case 2:
        {
            if(key.code==sf::Keyboard::Key::Down)
            {
                std::vector<int> focus=keyboard_.getFocus();
                focus[0]++;
                if(focus[0]>row)
                {
                    focus[0]=1;
                }
                keyboard_.setFocus(focus);
                //std::cout<<focus[0]<<" "<<focus[1]<<std::endl;
            }

            if(key.code==sf::Keyboard::Key::Up)
            {
                std::vector<int> focus=keyboard_.getFocus();
                focus[0]--;
                if(focus[0]<1)
                {
                    focus[0]=row;
                }
                keyboard_.setFocus(focus);
                //std::cout<<focus[0]<<" "<<focus[1]<<std::endl;
            }

            if(key.code==sf::Keyboard::Key::Right)
            {
                std::vector<int> focus=keyboard_.getFocus();
                focus[1]++;
                if(focus[1]>column)
                {
                    focus[1]=1;
                }
                keyboard_.setFocus(focus);
                //std::cout<<focus[0]<<" "<<focus[1]<<std::endl;
            }

            if(key.code==sf::Keyboard::Key::Left)
            {
                std::vector<int> focus=keyboard_.getFocus();
                focus[1]--;
                if(focus[1]<1)
                {
                    focus[1]=column;
                }
                keyboard_.setFocus(focus);
                //std::cout<<focus[0]<<" "<<focus[1]<<std::endl;
            }

            if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
            {
                load_replay();
                phase_=1;
            }

            if(key.code==sf::Keyboard::Key::Z)
            {
                keyboard_.addString();
                std::vector<int> focus=keyboard_.getFocus();
                if((focus[0]==7)&&(focus[1]==13))
                {
                    std::string file_name="replay/replay_"+std::to_string(focus_)+".rep";
                    if(game_!=nullptr)
                    {
                        //长度不足补空格，超长截断
                        std::string replay_name=keyboard_.getString();
                        replay_name.resize(static_cast<std::size_t>(max_input_length),' ');
                        game_->saveReplay(file_name,replay_name);
                        load_replay();
                        phase_=1;
                    }
                    else
                    {
                        std::cout<<"save error!"<<std::endl;
                    }
                }
            }
        }
    
    default:
        break;
    }
}