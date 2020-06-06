#include "startscreen.hpp"

#include <TGUI/TGUI.hpp>
#include <string.h>

//#define DEBUG_STARTSCREEN

void sig_button(sf::RenderWindow & window, bool & is_back)
{
    window.close();
    is_back = true;
}

int drawstartscreen(std::string& str)//(sf::Font font)
{
    bool is_back = false;

    sf::View view; // Окно просмотра.
    sf::RenderWindow window; //создается окно
    sf::ContextSettings context; //какие-то связанные настройки

    tgui::Gui gui{window};

    auto editBox = tgui::EditBox::create();
    //editBox->setRenderer(theme.getRenderer("EditBox"));
    editBox->setSize(365, 30);
    editBox->setTextSize(20);
    editBox->setPosition(0, 100);
    editBox->setDefaultText("Click to enter RE, press ENTER when you did it.");
    gui.add(editBox);
    //    editBox->draw();

    auto button = tgui::Button::create();
    button->setPosition(400, 100);
    button->setText("BACK TO MENU");
    button->setSize(100, 30);
    button->connect("pressed", sig_button, std::ref(window), std::ref(is_back));
    gui.add(button);

    int scale_base = 2; //изменение масштаба
    int scale_power = 0; //изменение масштаба

    window.create(sf::VideoMode(800,600)/*ширина, высота*/, "Rubbur"/*имя окна*/, sf::Style::Default, context); // Создание окна.
    window.setFramerateLimit(60); // Ограничение на частоту обновления экрана.

    view.setCenter(200.0f, 100.0f); //координаты центра экрана
    view.setSize(static_cast<sf::Vector2f>(window.getSize())); //чтобы отображалась область, совпадающую с экраном
    view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f)); //все, что показывает view, будет на экране
    window.setView(view); //задается камера окну
    gui.setView(view);

    sf::Font font;
    if (!font.loadFromFile("../../SourceCodePro-Regular.otf"))
    {
        std::cout << "ERROR!!!" << std::endl;
    }

    sf::Text greeting;
    greeting.setFont(font); // font is a sf::Font
    greeting.setString("RUBBUR");
    greeting.setCharacterSize(100); // in pixels, not points!
    greeting.setFillColor(sf::Color::Red);
    greeting.setPosition(0,0);

    std::vector<sf::Text> rules;
    sf::Text rule;
    rule.setFont(font);
    rule.setCharacterSize(30);
    rule.setFillColor(sf::Color::Red);
    rule.setPosition(0,130);
    rule.setString("RULES");
    rules.push_back(rule);
    rule.setCharacterSize(20);
    rule.setPosition(0,160);
    rule.setString("1. Use only Latin letters or digits.");
    rules.push_back(rule);
    rule.setPosition(0,180);
    rule.setString("2. Use '+' for union, '*' for iteration.");
    rules.push_back(rule);
    rule.setPosition(0,200);
    //rule.setString("3. Two symbols one by one are treated as concatenation.");
    rule.setString("3. Write symbols one by one for concatenation.");
    rules.push_back(rule);
    rule.setPosition(0,220);
    rule.setString("4. DO NOT USE EMPTY STRING!!!");
    rules.push_back(rule);

    // set the text style
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Vector2f mouse_position; //положение мыши
    sf::Event window_event; //событие мыши
    while (is_back == false)
    {
        while (window.isOpen()) //пока открыто окно
        {
            while (window.pollEvent(window_event)) //опрос событий, пока есть необработанные
            {
                switch (window_event.type) //switch по событиям
                {
                    case sf::Event::Closed: //закрытие
                    {
                        return 1;
                        break;
                    }
                    case sf::Event::Resized: //изменился размер окна - перенастройка размеров
                    {
                        view.setSize(static_cast<sf::Vector2f>(window.getSize()) * static_cast<float>(pow(scale_base, scale_power)));
                        view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
                        window.setView(view);
                        gui.setView(view);

                        break;
                    }
                    case sf::Event::MouseButtonPressed: //нажата кнопка мыши
                    {
                        switch (window_event.mouseButton.button) //какая клавиша
                        {
                            case sf::Mouse::Left: //куда нажали
                            {
                                mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                        break;
                    }
                    case sf::Event::MouseButtonReleased: //отпущена кнопка мыши
                    {
                        switch (window_event.mouseButton.button)
                        {
                            case sf::Mouse::Left:
                            {
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                        break;
                    }
                    case sf::Event::MouseWheelMoved: //покручено колесико
                    {

                        if (window_event.mouseWheel.delta > 0) //изменение масштаба
                        {
                            --scale_power;
                        }
                        else
                        {
                            ++scale_power;
                        }
                        view.setSize(static_cast<sf::Vector2f>(window.getSize()) * static_cast<float>(pow(scale_base, scale_power)));
                        window.setView(view);
                        mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        break;
                    }
                    case sf::Event::KeyPressed: //нажата клавиша клавиатуры
                    {
                        switch (window_event.key.code)
                        {
                            case sf::Keyboard::R: //какая-то клавиша
                            {
                                break;
                            }
                            ///////
                            case sf::Keyboard::Enter: //какая-то клавиша
                            {
                                const sf::String& edinput = editBox->getText();
                                std::string in_put = edinput;
                                #ifdef DEBUG_STARTSCREEN
                                std::cout << in_put << std::endl;
                                #endif
                                str = in_put;
                                window.close();
                                return 0;
                                break;
                            }
                            case sf::Keyboard::Escape:
                            {
                                window.close();
                                return 1;
                                break;
                            }
                            ////////////
                            default:
                            {
                                break;
                            }
                        }
                    }
                    default:
                    {
                        break;
                    }
                }
                gui.handleEvent(window_event);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window.hasFocus()) //зажатая клавиша мыши
            {
                sf::Vector2f new_mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                view.move(mouse_position - new_mouse_position);
                window.setView(view);
                gui.setView(view);
            }

            window.clear(sf::Color::Black); //очистить экран

            window.draw(greeting);
            for(size_t i = 0; i < 5; ++i)
            {
                window.draw(rules[i]);
            }
            //window.draw(text);
            gui.draw();

            //window.draw(circle);
            window.display();
        }
        if (is_back == true)
        {
            window.close();
            return 3;
        }
    }
    return 2;
}
