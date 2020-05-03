#include "tree.hpp"
#include "grammar.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Grexpnode.hpp"
#include <unordered_map>
#include <sstream>

//#define DEBUG_DRAWTREE

void depthsearch(std::vector<std::shared_ptr<Node<NData>>>& tree, std::shared_ptr<Node<NData>> node)
{
    tree.push_back(node);
    for (auto child : node->children)
    {
        depthsearch(tree, child);
    }
    //    depthsearch(tree, *(++node->children.begin()));
}

void makegvec(std::vector<std::shared_ptr<Node<NData>>>& tree, std::vector<std::shared_ptr<GRExpNode>>& nodes,
              std::unordered_map<Node<NData>*, std::shared_ptr<GRExpNode>>& table)
{
    //заполняем массив
    for (size_t i = 0; i < tree.size(); ++i)
    {
        nodes.push_back(std::make_shared<GRExpNode>());
    }
    //заполняем данными
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        nodes[i]->data = tree[i];
        table.insert(std::make_pair(tree[i].get(), nodes[i]));
    }
    nodes[0]->coords.x = 0;
    nodes[0]->coords.y = 0;
}

void makegr(std::shared_ptr<GRExpNode> root, std::unordered_map<Node<NData>*, std::shared_ptr<GRExpNode>>& table)
{
    //for (auto iter = root->data->children.begin(); iter != root->data->children.end(); ++iter)
    //{
    switch (root->data->value.type)
    {
        case NData::Type::Conc:
        {
            auto c1 = *(root->data->children.begin());
            auto c2 = *(++(root->data->children.begin()));
            table[c1.get()]->coords.x = root->coords.x - (25.f * pow(2, (root->data->value.depth)));
            //table выдает Node
            table[c1.get()]->coords.y = root->coords.y + (50.f * pow(2, (root->data->value.depth)));
            table[c2.get()]->coords.x = root->coords.x + (25.f * pow(2, (root->data->value.depth)));
            //table выдает Node
            table[c2.get()]->coords.y = root->coords.y + (50.f * pow(2, (root->data->value.depth)));
            makegr(table[c1.get()], table);
            makegr(table[c2.get()], table);
            break;
        }
        case NData::Type::Union:
        {
            auto c1 = root->data->children.begin()->get();
            auto c2 = (++(root->data->children.begin()))->get();
            table[c1]->coords.x = root->coords.x - (25.f * pow(2, (root->data->value.depth)));
            //table выдает Node
            table[c1]->coords.y = root->coords.y + (50.f * pow(2, (root->data->value.depth)));
            table[c2]->coords.x = root->coords.x + (25.f * pow(2, (root->data->value.depth)));
            //table выдает Node
            table[c2]->coords.y = root->coords.y + (50.f * pow(2, (root->data->value.depth)));
            makegr(table[c1], table);
            makegr(table[c2], table);
            break;
        }
        case NData::Type::Iter:
        {
            auto c1 = root->data->children.begin()->get();
            table[c1]->coords.x = root->coords.x;
            //table выдает Node
            table[c1]->coords.y = root->coords.y + (50.f * pow(2, (root->data->value.depth)));
            makegr(table[c1], table);
            break;
        }
        case NData::Type::Char:
        {
            break;
        }
    }
}

void drawtree(std::shared_ptr<Node<NData>> root)
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
    std::vector<std::shared_ptr<Node<NData>>> tree;
    depthsearch(tree, root);

    std::vector<std::shared_ptr<GRExpNode>> nodes;
    std::unordered_map<Node<NData>*, std::shared_ptr<GRExpNode>> table;
    makegvec(tree, nodes, table);

    makegr(table[root.get()], table);
    //, root);

    //size_t i = 0;
    //int R = root->value.depth;
    //while (i < nodes.size())
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        //круг
        nodes[i]->circle.setRadius(10.0f);
        nodes[i]->circle.setOrigin(nodes[i]->circle.getRadius(), nodes[i]->circle.getRadius()); //чтобы координата центра была положением
        nodes[i]->circle.setPosition(nodes[i]->coords.x, nodes[i]->coords.y);
        nodes[i]->circle.setFillColor(sf::Color::White);
        //nodes[i]->circle.setOutlineColor(sf::Color::Red);
        nodes[i]->circle.setOutlineThickness(2.0f);

        switch (nodes[i]->data->value.type)
        {
            case NData::Type::Char:
            {
                nodes[i]->circle.setOutlineColor(sf::Color::White);
                //++i;
                break;
            }
            case NData::Type::Conc:
            {
                nodes[i]->circle.setOutlineColor(sf::Color::Red);
                //первая линия
                nodes[i]->lines.push_back(std::array<sf::Vertex, 2>());
                nodes[i]->lines[0][0] = sf::Vertex(nodes[i]->coords);
                nodes[i]->lines[0][1] = sf::Vertex(sf::Vector2f(nodes[i]->coords.x - (25.f * pow(2, (nodes[i]->data->value.depth))),
                                                                nodes[i]->coords.y + (50.f * pow(2, (nodes[i]->data->value.depth)))));

                #ifdef DEBUG_DRAWTREE
                std::cout << "CONC, C1 = (" << nodes[i]->lines[0][0].position.x << ";" << nodes[i]->lines[0][0].position.y << ") -> ("
                          << nodes[i]->lines[0][1].position.x << ";" << nodes[i]->lines[0][1].position.y << ")" << std::endl;
                #endif

                //вторая линия
                nodes[i]->lines.push_back(std::array<sf::Vertex, 2>());
                nodes[i]->lines[1][0] = sf::Vertex(nodes[i]->coords);
                nodes[i]->lines[1][1] = sf::Vertex(sf::Vector2f(nodes[i]->coords.x + (25.f * pow(2, (nodes[i]->data->value.depth))),
                                                                nodes[i]->coords.y + (50.f * pow(2, (nodes[i]->data->value.depth)))));

                #ifdef DEBUG_DRAWTREE
                std::cout << "CONC, C1 = (" << nodes[i]->lines[1][0].position.x << ";" << nodes[i]->lines[1][0].position.y << ") -> ("
                          << nodes[i]->lines[1][1].position.x << ";" << nodes[i]->lines[1][1].position.y << ")" << std::endl;
                #endif

                //++i;
                break;
            }
            case NData::Type::Union:
            {
                nodes[i]->circle.setOutlineColor(sf::Color::Blue);
                //первая линия
                nodes[i]->lines.push_back(std::array<sf::Vertex, 2>());
                nodes[i]->lines[0][0] = sf::Vertex(nodes[i]->coords);
                nodes[i]->lines[0][1] = sf::Vertex(sf::Vector2f(nodes[i]->coords.x - (25.f * pow(2, (nodes[i]->data->value.depth))),
                                                                nodes[i]->coords.y + (50.f * pow(2, (nodes[i]->data->value.depth)))));

                #ifdef DEBUG_DRAWTREE
                std::cout << "UNION, C1 = (" << nodes[i]->lines[0][0].position.x << ";" << nodes[i]->lines[0][0].position.y << ") -> ("
                          << nodes[i]->lines[0][1].position.x << ";" << nodes[i]->lines[0][1].position.y << ")" << std::endl;
                #endif

                //вторая линия
                nodes[i]->lines.push_back(std::array<sf::Vertex, 2>());
                nodes[i]->lines[1][0] = sf::Vertex(nodes[i]->coords);
                nodes[i]->lines[1][1] = sf::Vertex(sf::Vector2f(nodes[i]->coords.x + (25.f * pow(2, (nodes[i]->data->value.depth))),
                                                                nodes[i]->coords.y + (50.f * pow(2, (nodes[i]->data->value.depth)))));

                #ifdef DEBUG_DRAWTREE
                std::cout << "UNION, C1 = (" << nodes[i]->lines[1][0].position.x << ";" << nodes[i]->lines[1][0].position.y << ") -> ("
                          << nodes[i]->lines[1][1].position.x << ";" << nodes[i]->lines[1][1].position.y << ")" << std::endl;
                #endif

                //++i;
                break;
            }
            case NData::Type::Iter:
            {
                nodes[i]->circle.setOutlineColor(sf::Color::Green);
                //единственная линия
                nodes[i]->lines.push_back(std::array<sf::Vertex, 2>());
                nodes[i]->lines[0][0] = sf::Vertex(nodes[i]->coords);
                nodes[i]->lines[0][1] = sf::Vertex(sf::Vector2f(nodes[i]->coords.x,
                                                                nodes[i]->coords.y + (50.f *  pow(2, (nodes[i]->data->value.depth)))));
                //хлам
                nodes[i]->lines.push_back(std::array<sf::Vertex, 2>());
                nodes[i]->lines[1][0] = sf::Vertex(nodes[i]->coords);
                nodes[i]->lines[1][1] = sf::Vertex(nodes[i]->coords);

                #ifdef DEBUG_DRAWTREE
                std::cout << "ITER, CHILD = (" << nodes[i]->lines[0][0].position.x << ";" << nodes[i]->lines[0][0].position.y << ") -> ("
                          << nodes[i]->lines[0][1].position.x << ";" << nodes[i]->lines[0][1].position.y << ")" << std::endl;
                #endif

                //++i;
                break;
            }
        }

    }
    /*
      {
      sf::Vertex(sf::Vector2f(10.f, 10.f)),
      sf::Vertex(sf::Vector2f(150.f, 150.f))
      };
    */

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

        for (size_t i = 0; i < nodes.size(); ++i)
        {
            //рисование обеих линий
            for (size_t j = 0; j < nodes[i]->lines.size(); ++j)
            {
                window.draw(nodes[i]->lines[j].data(), 2, sf::Lines);
            }
            window.draw(nodes[i]->circle);
        }

        //window.draw(circle);
        window.display();
    }
}

size_t makefollow (std::string str, std::vector<std::set<std::pair<size_t, char>>>& followpos)//(std::vector<std::shared_ptr<Node<NData>>>& tree)//, std::shared_ptr<Node<NData>> root)
{
    size_t max_pos = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        switch (str[i])
        {
            case '(' :
            {
                break;
            }
            case ')' :
            {
                break;
            }
            case '+' :
            {
                break;
            }
            default :
            {
                max_pos++;
                break;
            }
        }
    }
    //создание таблицы followpos (реализована массивом)
    for (size_t i = 0; i < max_pos; ++i)
    {
        followpos.push_back(std::set<std::pair<size_t, char>>());
    }
    return max_pos;
}

void countfollow (std::shared_ptr<Node<NData>> root,  std::vector<std::set<std::pair<size_t, char>>>& followpos, size_t max_pos)
{
    switch (root->value.type)
    {
        case NData::Type::Conc:
        {
            auto c1 = *(root->children.begin());
            auto c2 = *(++(root->children.begin()));
            for (size_t i = 0; i < max_pos; ++i)
            {
                auto iter = c1->value.lastpos.lower_bound(std::make_pair(i, 0));
                if ((iter != c1->value.lastpos.end()) && (iter->first == i))
                {
                    for (size_t j = 0; j < max_pos; ++j)
                    {
                        auto jter = c2->value.firstpos.lower_bound(std::make_pair(j, 0));
                        if ((jter != c2->value.firstpos.end()) && (jter->first == j))
                        {
                            followpos[i].insert(*jter);
                        }
                    }
                }
            }
            countfollow (c1, followpos, max_pos);
            countfollow (c2, followpos, max_pos);
            break;
        }
        case NData::Type::Union:
        {
            auto c1 = *(root->children.begin());
            auto c2 = *(++(root->children.begin()));
            countfollow(c1, followpos, max_pos);
            countfollow(c2, followpos, max_pos);
            break;
        }
        case NData::Type::Iter:
        {
            auto c1 = *(root->children.begin());
            for (size_t i = 0; i < max_pos; ++i)
            {
                auto iter = c1->value.lastpos.lower_bound(std::make_pair(i, 0));
                //std::cout << "i = " << i << "; (" << iter->first << ", " << iter->second << ")" << std::endl;
                if ((iter != c1->value.lastpos.end()) && (iter->first == i))
                {
                    for (size_t j = 0; j < max_pos; ++j)
                    {
                        auto jter = c1->value.firstpos.lower_bound(std::make_pair(j, 0));
                        if ((jter != c1->value.firstpos.end()) && (jter->first == j))
                        {
                            followpos[i].insert(*jter);
                        }
                    }
                }
            }
            countfollow(c1, followpos, max_pos);
            break;
        }
        case NData::Type::Char:
        {
            break;
        }
    }
}

int main()
{
    std::string str;
    std::cin >> str;
    str = "(" + str + ")#";

    std::stringstream stream(str);

    std::shared_ptr<Node<NData>> root;
    yy::parser parse(stream, root);
    parse();
    std::cout << root.get() << std::endl;
    calculate(*root);
    std::cout << root->value.firstpos.size() << ' '
              << root->value.is_nullable << ' '
              << root->value.lastpos.size() << std::endl;

    std::vector<std::set<std::pair<size_t, char>>> followpos;
    size_t max_pos = makefollow(str, followpos);

    std::cout << max_pos << std::endl;

    countfollow(root, followpos, max_pos);

    for(size_t i = 0; i < followpos.size(); ++i)
    {
        std::cout << "i = " << i;
        for(auto item : followpos[i])
        {
            std::cout << "(" << item.first << ";" << item.second << "), ";
        }
        std::cout << std::endl;
    }
    drawtree(root);

    return 0;
}
