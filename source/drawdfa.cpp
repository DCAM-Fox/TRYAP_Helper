#include "drawdfa.hpp"

//#define DEBUG_DRAWDFA

void makeaut(DFA& dfa, std::vector<std::shared_ptr<DFState>>& automata)
{
    automata = dfa.states;
}

void makebase(std::vector<std::shared_ptr<DFState>>& automata, std::vector<std::shared_ptr<GState>>& gstates, std::unordered_map<DFState*, std::shared_ptr<GState>>& table)
{
    //заполняем массив
    for (size_t i = 0; i < automata.size(); ++i)
    {
        gstates.push_back(std::make_shared<GState>());
    }
    //заполняем данными
    for (size_t i = 0; i < automata.size(); ++i)
    {
        gstates[i]->data = automata[i];
        table.insert(std::make_pair(automata[i].get(), gstates[i]));
    }
    /*
      gstates[0]->coords.x = 0;
      gstates[0]->coords.y = 0;
    */
}

void makelayout(std::vector<std::shared_ptr<GState>> gstates)
{
    for(size_t i = 0; i < gstates.size(); ++i)
    {
        gstates[i]->coords.x = 50*i;
        gstates[i]->coords.y = 0;

        #ifdef DEBUG_DRAWDFA
        std::cout << "i = " << i << "; coords: (" << gstates[i]->coords.x << ";" << gstates[i]->coords.y << ")" << std::endl;
        #endif
    }
}

void drawdfa(DFA& dfa)
{
    sf::View view; // Окно просмотра.
    sf::RenderWindow window; //создается окно
    sf::ContextSettings context; //какие-то связанные настройки

    int scale_base = 2; //изменение масштаба
    int scale_power = 0; //изменение масштаба

    window.create(sf::VideoMode(600, 400)/*ширина, высота*/, "Rubbur"/*имя окна*/, sf::Style::Default, context); // Создание окна.
    window.setFramerateLimit(60); // Ограничение на частоту обновления экрана.

    view.setCenter(0.0f, 0.0f); //координаты центра экрана
    view.setSize(static_cast<sf::Vector2f>(window.getSize())); //чтобы отображалась область, совпадающую с экраном
    view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f)); //все, что показывает view, будет на экране
    window.setView(view); //задается камера окну

    /*
      sf::CircleShape circle;
      circle.setRadius(10.0f);
      circle.setOrigin(circle.getRadius(), circle.getRadius()); //чтобы координата центра была положением
      circle.setPosition(10.0f, 20.0f);
      circle.setFillColor(sf::Color::White);
      circle.setOutlineColor(sf::Color::Red);
      circle.setOutlineThickness(2.0f);
    */

    /*На глубине h запишем место для 2^h вершин; т.е. они будут на расстоянии 50*2^(root.depth - h) друг от друга*/
    std::vector<std::shared_ptr<DFState>> automata;
    std::vector<std::shared_ptr<GState>> gstates;
    std::unordered_map<DFState*, std::shared_ptr<GState>> table;

    makeaut(dfa, automata);

    makebase(automata, gstates, table);

    makelayout(gstates);

    for (size_t i = 0; i < gstates.size(); ++i)
    {
        //круг
        gstates[i]->circle.setRadius(20.0f);
        gstates[i]->circle.setOrigin(gstates[i]->circle.getRadius(), gstates[i]->circle.getRadius()); //чтобы координата центра была положением
        gstates[i]->circle.setPosition(gstates[i]->coords.x, gstates[i]->coords.y);
        gstates[i]->circle.setFillColor(sf::Color::White);
        gstates[i]->circle.setOutlineColor(sf::Color::Red);
        gstates[i]->circle.setOutlineThickness(2.0f);

        if(gstates[i]->data->is_accepting == true)
        {
            gstates[i]->ring.setRadius(17.0f);
            gstates[i]->ring.setOrigin(gstates[i]->ring.getRadius(), gstates[i]->ring.getRadius()); //чтобы координата центра была положением
            gstates[i]->ring.setPosition(gstates[i]->coords.x, gstates[i]->coords.y);
            gstates[i]->ring.setFillColor(sf::Color::White);
            gstates[i]->ring.setOutlineColor(sf::Color::Red);
            gstates[i]->ring.setOutlineThickness(1.0f);
        }
        else
        {
            gstates[i]->ring.setOrigin(gstates[i]->ring.getRadius(), gstates[i]->ring.getRadius()); //чтобы координата центра была положением
            gstates[i]->ring.setPosition(gstates[i]->coords.x, gstates[i]->coords.y);
            gstates[i]->ring.setFillColor(sf::Color::White);
            gstates[i]->ring.setRadius(0.0f);
        }
        /*
          switch (gstates[i]->data->value.type)
          {
          case NData::Type::Char:
          {
          gstates[i]->circle.setOutlineColor(sf::Color::White);
          //++i;
          break;
          }
          case NData::Type::Conc:
          {
          gstates[i]->circle.setOutlineColor(sf::Color::Red);
          //первая линия
          gstates[i]->lines.push_back(std::array<sf::Vertex, 2>());
          gstates[i]->lines[0][0] = sf::Vertex(gstates[i]->coords);
          gstates[i]->lines[0][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x - (25.f * pow(2, (gstates[i]->data->value.depth))),
          gstates[i]->coords.y + (50.f * pow(2, (gstates[i]->data->value.depth)))));

          #ifdef DEBUG_DRAWTREE
          std::cout << "CONC, C1 = (" << gstates[i]->lines[0][0].position.x << ";" << gstates[i]->lines[0][0].position.y << ") -> ("
          << gstates[i]->lines[0][1].position.x << ";" << gstates[i]->lines[0][1].position.y << ")" << std::endl;
          #endif

          //вторая линия
          gstates[i]->lines.push_back(std::array<sf::Vertex, 2>());
          gstates[i]->lines[1][0] = sf::Vertex(gstates[i]->coords);
          gstates[i]->lines[1][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x + (25.f * pow(2, (gstates[i]->data->value.depth))),
          gstates[i]->coords.y + (50.f * pow(2, (gstates[i]->data->value.depth)))));

          #ifdef DEBUG_DRAWTREE
          std::cout << "CONC, C1 = (" << gstates[i]->lines[1][0].position.x << ";" << gstates[i]->lines[1][0].position.y << ") -> ("
          << gstates[i]->lines[1][1].position.x << ";" << gstates[i]->lines[1][1].position.y << ")" << std::endl;
          #endif

          //++i;
          break;
          }
          case NData::Type::Union:
          {
          gstates[i]->circle.setOutlineColor(sf::Color::Blue);
          //первая линия
          gstates[i]->lines.push_back(std::array<sf::Vertex, 2>());
          gstates[i]->lines[0][0] = sf::Vertex(gstates[i]->coords);
          gstates[i]->lines[0][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x - (25.f * pow(2, (gstates[i]->data->value.depth))),
          gstates[i]->coords.y + (50.f * pow(2, (gstates[i]->data->value.depth)))));

          #ifdef DEBUG_DRAWTREE
          std::cout << "UNION, C1 = (" << gstates[i]->lines[0][0].position.x << ";" << gstates[i]->lines[0][0].position.y << ") -> ("
          << gstates[i]->lines[0][1].position.x << ";" << gstates[i]->lines[0][1].position.y << ")" << std::endl;
          #endif

          //вторая линия
          gstates[i]->lines.push_back(std::array<sf::Vertex, 2>());
          gstates[i]->lines[1][0] = sf::Vertex(gstates[i]->coords);
          gstates[i]->lines[1][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x + (25.f * pow(2, (gstates[i]->data->value.depth))),
          gstates[i]->coords.y + (50.f * pow(2, (gstates[i]->data->value.depth)))));

          #ifdef DEBUG_DRAWTREE
          std::cout << "UNION, C1 = (" << gstates[i]->lines[1][0].position.x << ";" << gstates[i]->lines[1][0].position.y << ") -> ("
          << gstates[i]->lines[1][1].position.x << ";" << gstates[i]->lines[1][1].position.y << ")" << std::endl;
          #endif

          //++i;
          break;
          }
          case NData::Type::Iter:
          {
          gstates[i]->circle.setOutlineColor(sf::Color::Green);
          //единственная линия
          gstates[i]->lines.push_back(std::array<sf::Vertex, 2>());
          gstates[i]->lines[0][0] = sf::Vertex(gstates[i]->coords);
          gstates[i]->lines[0][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x,
          gstates[i]->coords.y + (50.f *  pow(2, (gstates[i]->data->value.depth)))));
          //хлам
          gstates[i]->lines.push_back(std::array<sf::Vertex, 2>());
          gstates[i]->lines[1][0] = sf::Vertex(gstates[i]->coords);
          gstates[i]->lines[1][1] = sf::Vertex(gstates[i]->coords);

          #ifdef DEBUG_DRAWTREE
          std::cout << "ITER, CHILD = (" << gstates[i]->lines[0][0].position.x << ";" << gstates[i]->lines[0][0].position.y << ") -> ("
          << gstates[i]->lines[0][1].position.x << ";" << gstates[i]->lines[0][1].position.y << ")" << std::endl;
          #endif

          //++i;
          break;
          }
          }

          }*/
        /*
          {
          sf::Vertex(sf::Vector2f(10.f, 10.f)),
          sf::Vertex(sf::Vector2f(150.f, 150.f))
          };
        */
    }
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
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window.hasFocus()) //зажатая клавиша мыши
        {
            sf::Vector2f new_mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            view.move(mouse_position - new_mouse_position);
            window.setView(view);
        }

        window.clear(sf::Color::Black); //очистить экран

        for (size_t i = 0; i < gstates.size(); ++i)
        {
            /*
            //рисование обеих линий
            for (size_t j = 0; j < gstates[i]->lines.size(); ++j)
            {
            window.draw(gstates[i]->lines[j].data(), 2, sf::Lines);
            }
            */
            #ifdef DEBUG_DRAWDFA
            std::cout << i << ": circle: (" << gstates[i]->coords.x << ";" << gstates[i]->coords.y << "), ring: "<< gstates[i]->ring.getRadius() << std::endl;
            #endif
            window.draw(gstates[i]->circle);
            window.draw(gstates[i]->ring);
        }

        //window.draw(circle);
        window.display();
    }
}
