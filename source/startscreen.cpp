#include "startscreen.hpp"

#include <TGUI/TGUI.hpp>
#include <string.h>

void drawstartscreen(std::string& str)//(sf::Font font)
{
    sf::View view; // Окно просмотра.
    sf::RenderWindow window; //создается окно
    sf::ContextSettings context; //какие-то связанные настройки


    tgui::Gui gui{window};

    auto editBox = tgui::EditBox::create();
    //editBox->setRenderer(theme.getRenderer("EditBox"));
    editBox->setSize(365, 30);
    editBox->setTextSize(20);
    editBox->setPosition(0, 100);
    editBox->setDefaultText("Click to edit text...");
    gui.add(editBox);
    //    editBox->draw();

    int scale_base = 2; //изменение масштаба
    int scale_power = 0; //изменение масштаба

    window.create(sf::VideoMode(600, 400)/*ширина, высота*/, "Rubbur"/*имя окна*/, sf::Style::Default, context); // Создание окна.
    window.setFramerateLimit(60); // Ограничение на частоту обновления экрана.

    view.setCenter(0.0f, 0.0f); //координаты центра экрана
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

    // set the text style
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Vector2f mouse_position; //положение мыши
    sf::Event window_event; //событие мыши
    while (window.isOpen()) //пока открыто окно
    {
        while (window.pollEvent(window_event)) //опрос событий, пока есть необработанные
        {
            switch (window_event.type) //switch по событиям
            {
                case sf::Event::Closed: //закрытие
                {
                    return;
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
                            std::cout << in_put << std::endl;
                            str = in_put;
                            window.close();
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

/*
  sf::Text heading;
  heading.setFont(font); // font is a sf::Font
  heading.setString("RUBBUR");
  heading.setCharacterSize(100); // in pixels, not points!
  heading.setFillColor(sf::Color::Red);
  heading.setPosition(0.0f, 0.0f);

  tgui::Gui gui{window};

  auto editBox = tgui::EditBox::create();
  //editBox->setRenderer(theme.getRenderer("EditBox"));
  editBox->setSize(300, 30);
  editBox->setTextSize(20);
  editBox->setPosition(10, 270);
  editBox->setDefaultText("Click to edit text...");
  gui.add(editBox);

  sf::Vector2f mouse_position; //положение мыши
  sf::Event window_event; //событие мыши
  while (window.isOpen()) //пока открыто окно
  {
  while (window.pollEvent(window_event)) //опрос событий, пока есть необработанные
  {
  switch (window_event.type) //switch по событиям
  {
  case sf::Event::Closed: //закрытие
  {
  return;
  break;
  }
  case sf::Event::Resized: //изменился размер окна - перенастройка размеров
  {
  view.setSize(static_cast<sf::Vector2f>(window.getSize()) * static_cast<float>(pow(scale_base, scale_power)));
  view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
  window.setView(view);

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

  window.draw(greeting);
  gui.draw();
  window.display();
  }
*/
