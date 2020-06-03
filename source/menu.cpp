#include "menu.hpp"

#include <TGUI/TGUI.hpp>
#include <string.h>

//#define DEBUG_STARTSCREEN

void sig_re_dfa(sf::RenderWindow & window, int & algo)
{
    window.close();
    algo = 0;
}
void sig_re_nfa(sf::RenderWindow & window, int & algo)
{
    window.close();
    algo = 1;
}
void sig_minim(sf::RenderWindow & window, int & algo)
{
    window.close();
    algo = 2;
}
void sig_determ(sf::RenderWindow & window, int & algo)
{
    window.close();
    algo = 3;
}
void sig_aho(sf::RenderWindow & window, int & algo)
{
    window.close();
    algo = 4;
}
void sig_mag(sf::RenderWindow & window, int & algo)
{
    window.close();
    algo = 5;
}
void sig_ll(sf::RenderWindow & window, int & algo)
{
    window.close();
    algo = 6;
}
void sig_lr(sf::RenderWindow & window, int & algo)
{
    window.close();
    algo = 7;
}

int drawmenu()//(sf::Font font)
{
    sf::View view; // Окно просмотра.
    sf::RenderWindow window; //создается окно
    sf::ContextSettings context; //какие-то связанные настройки


    tgui::Gui gui{window};

    int scale_base = 2; //изменение масштаба
    int scale_power = 0; //изменение масштаба

    window.create(sf::VideoMode(800,600)/*ширина, высота*/, "Rubbur"/*имя окна*/, sf::Style::Default, context); // Создание окна.
    window.setFramerateLimit(60); // Ограничение на частоту обновления экрана.

    view.setCenter(200.0f, 100.0f); //координаты центра экрана
    view.setSize(static_cast<sf::Vector2f>(window.getSize())); //чтобы отображалась область, совпадающую с экраном
    view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f)); //все, что показывает view, будет на экране
    window.setView(view); //задается камера окну
    gui.setView(view);

    int algo = -1;

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
    greeting.setPosition(0,-120);

    auto re_dfa = tgui::Button::create();
    re_dfa->setPosition(0, 0);
    re_dfa->setText("RE -> DFA");
    re_dfa->setSize(100, 30);
    re_dfa->connect("pressed", sig_re_dfa, std::ref(window), std::ref(algo));
    gui.add(re_dfa);

    auto re_nfa = tgui::Button::create();
    re_nfa->setPosition(250, 0);
    re_nfa->setText("RE -> NFA");
    re_nfa->setSize(100, 30);
    re_nfa->connect("pressed", sig_re_nfa, std::ref(window), std::ref(algo));
    gui.add(re_nfa);

    auto minim = tgui::Button::create();
    minim->setPosition(0, 50);
    minim->setText("MINIMIZE");
    minim->setSize(100, 30);
    minim->connect("pressed", sig_minim, std::ref(window), std::ref(algo));
    gui.add(minim);

    auto determ = tgui::Button::create();
    determ->setPosition(250, 50);
    determ->setText("DETERMINE");
    determ->setSize(100, 30);
    determ->connect("pressed", sig_determ, std::ref(window), std::ref(algo));
    gui.add(determ);

    auto aho = tgui::Button::create();
    aho->setPosition(0, 100);
    aho->setText("DICTIONARY");
    aho->setSize(100, 30);
    aho->connect("pressed", sig_aho, std::ref(window), std::ref(algo));
    gui.add(aho);

    auto mag = tgui::Button::create();
    mag->setPosition(250, 100);
    mag->setText("CFL");
    mag->setSize(100, 30);
    mag->connect("pressed", sig_mag, std::ref(window), std::ref(algo));
    gui.add(mag);

    auto ll = tgui::Button::create();
    ll->setPosition(0, 150);
    ll->setText("LL");
    ll->setSize(100, 30);
    ll->connect("pressed", sig_ll, std::ref(window), std::ref(algo));
    gui.add(ll);

    auto lr = tgui::Button::create();
    lr->setPosition(250, 150);
    lr->setText("LR");
    lr->setSize(100, 30);
    lr->connect("pressed", sig_lr, std::ref(window), std::ref(algo));
    gui.add(lr);


    // set the text style
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Vector2f mouse_position; //положение мыши
    sf::Event window_event; //событие мыши
    while (algo == -1)
    {
        while (window.isOpen()) //пока открыто окно
        {
            while (window.pollEvent(window_event)) //опрос событий, пока есть необработанные
            {
                switch (window_event.type) //switch по событиям
                {
                    case sf::Event::Closed: //закрытие
                    {
                        return -1;
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
                                window.close();
                                return -1;
                                break;
                            }
                            case sf::Keyboard::Escape:
                            {
                                window.close();
                                return -1;
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
            //window.draw(text);
            gui.draw();

            //window.draw(circle);
            window.display();
        }
    }
    return algo;
}
