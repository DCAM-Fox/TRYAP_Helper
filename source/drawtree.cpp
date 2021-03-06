#include "drawtree.hpp"

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

//std::pair<float, float>
void makegr(std::shared_ptr<GRExpNode> root, std::unordered_map<Node<NData>*, std::shared_ptr<GRExpNode>>& table, std::pair<float, float> & sizes, float& minx, float& maxx, float& miny, float& maxy)
{
    //std::pair<float, float> sizes;
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
            makegr(table[c1.get()], table, sizes, minx, maxx, miny, maxy);
            makegr(table[c2.get()], table, sizes, minx, maxx, miny, maxy);
            if(table[c1.get()]->coords.x <= minx)
            {
                minx = table[c1.get()]->coords.x;
            }
            if(table[c1.get()]->coords.x >= maxx)
            {
                maxx = table[c1.get()]->coords.x;
            }
            if(table[c1.get()]->coords.y <= miny)
            {
                miny = table[c1.get()]->coords.y;
            }
            if(table[c1.get()]->coords.y >= maxy)
            {
                maxy = table[c1.get()]->coords.y;
            }
            if(table[c2.get()]->coords.x <= minx)
            {
                minx = table[c2.get()]->coords.x;
            }
            if(table[c2.get()]->coords.x >= maxx)
            {
                maxx = table[c2.get()]->coords.x;
            }
            if(table[c2.get()]->coords.y <= miny)
            {
                miny = table[c2.get()]->coords.y;
            }
            if(table[c2.get()]->coords.y >= maxy)
            {
                maxy = table[c2.get()]->coords.y;
            }
            //makegr(table[c1.get()], table, sizes, minx, maxx, miny, maxy);
            //makegr(table[c2.get()], table, sizes, minx, maxx, miny, maxy);
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
            //makegr(table[c1], table, sizes, minx, maxx, miny, maxy);
            //makegr(table[c2], table, sizes, minx, maxx, miny, maxy);
            if(table[c1]->coords.x <= minx)
            {
                minx = table[c1]->coords.x;
            }
            if(table[c1]->coords.x >= maxx)
            {
                maxx = table[c1]->coords.x;
            }
            if(table[c1]->coords.y <= miny)
            {
                miny = table[c1]->coords.y;
            }
            if(table[c1]->coords.y >= maxy)
            {
                maxy = table[c1]->coords.y;
            }
            if(table[c2]->coords.x <= minx)
            {
                minx = table[c2]->coords.x;
            }
            if(table[c2]->coords.x >= maxx)
            {
                maxx = table[c2]->coords.x;
            }
            if(table[c2]->coords.y <= miny)
            {
                miny = table[c2]->coords.y;
            }
            if(table[c2]->coords.y >= maxy)
            {
                maxy = table[c2]->coords.y;
            }
            makegr(table[c1], table, sizes, minx, maxx, miny, maxy);
            makegr(table[c2], table, sizes, minx, maxx, miny, maxy);
            break;
        }
        case NData::Type::Iter:
        {
            auto c1 = root->data->children.begin()->get();
            table[c1]->coords.x = root->coords.x;
            //table выдает Node
            table[c1]->coords.y = root->coords.y + (50.f * pow(2, (root->data->value.depth)));
            //makegr(table[c1], table, sizes, minx, maxx, miny, maxy);
            if(table[c1]->coords.x <= minx)
            {
                minx = table[c1]->coords.x;
            }
            if(table[c1]->coords.x >= maxx)
            {
                maxx = table[c1]->coords.x;
            }
            if(table[c1]->coords.y <= miny)
            {
                miny = table[c1]->coords.y;
            }
            if(table[c1]->coords.y >= maxy)
            {
                maxy = table[c1]->coords.y;
            }
            makegr(table[c1], table, sizes, minx, maxx, miny, maxy);
            break;
        }
        case NData::Type::Char:
        {
            break;
        }
    }
    sizes.first = maxx-minx;
    sizes.second = maxy - miny;
    std::cout << sizes.first << ", " << sizes.second << std::endl;
    //return sizes;
}

void sig_button(sf::RenderWindow & window, tgui::Gui & gui, sf::View & view, std::pair<float, float>& sizes, int scale_base, int & scale_power)
{
    //    view.setSize(sizes.first, sizes.second);

    sf::Vector2f vecsizes = (static_cast<sf::Vector2f>(window.getSize()) * static_cast<float>(pow(scale_base, scale_power)));

    int logx = static_cast<int>(ceil(log(sizes.first/vecsizes.x)/log(2)));
    int logy = static_cast<int>(ceil(log(sizes.second/vecsizes.y)/log(2)));
    std::cout << logx << ", " << logy << std::endl;
    int log = 0;
    if(logx >= logy)
    {
        log = logx;
    }
    else
    {
        log = logy;
    }
    scale_power = log;
    vecsizes = (static_cast<sf::Vector2f>(window.getSize()) * static_cast<float>(pow(scale_base, scale_power)));

    std::cout << vecsizes.x <<", "<<vecsizes.y<<std::endl;

    view.setSize(vecsizes);
    //view.setSize(static_cast<sf::Vector2f>(window.getSize()) * static_cast<float>(pow(scale_base, scale_power)));
    window.setView(view);
    gui.setView(view);
}

void sig_see_info_but(bool& see_info, tgui::Button& see_info_but)
{
    if(see_info == false)
    {
        see_info_but.setText("Hide info");
        see_info = true;
    }
    else
    {
        see_info_but.setText("See info");
        see_info = false;
    }
}

void makenodes(std::vector<std::shared_ptr<GRExpNode>> & nodes, sf::Font& font)
{
     for (size_t i = 0; i < nodes.size(); ++i)
    {
        //круг
        nodes[i]->circle.setRadius(20.0f);
        nodes[i]->circle.setOrigin(nodes[i]->circle.getRadius(), nodes[i]->circle.getRadius()); //чтобы координата центра была положением
        nodes[i]->circle.setPosition(nodes[i]->coords.x, nodes[i]->coords.y);
        nodes[i]->circle.setFillColor(sf::Color::White);
        //nodes[i]->circle.setOutlineColor(sf::Color::Red);
        nodes[i]->circle.setOutlineThickness(2.0f);

        nodes[i]->info.text.setFont(font); // font is a sf::Font
        // set the string to display
        // set the character size
        nodes[i]->info.text.setCharacterSize(20); // in pixels, not points!
        // set the color
        nodes[i]->info.text.setPosition(sf::Vector2(nodes[i]->coords.x - 10.0f, nodes[i]->coords.y - 10.0f));

        nodes[i]->info.nullable.setFont(font); // font is a sf::Font
        nodes[i]->info.nullable.setCharacterSize(15); // in pixels, not points!
        nodes[i]->info.nullable.setPosition(sf::Vector2(nodes[i]->coords.x + 20.0f, nodes[i]->coords.y));
        if(nodes[i]->data->value.is_nullable == true)
        {
            nodes[i]->info.nullable.setString("T");
        }
        else
        {
            nodes[i]->info.nullable.setString("F");
        }
        nodes[i]->info.nullable.setFillColor(sf::Color::White);

        std::string firstpos = "{";
        for (auto item : nodes[i]->data->value.firstpos)
        {
            firstpos = firstpos + "(";
            /////////////////////////////////////////////////////////////
            firstpos = firstpos + std::to_string(item.first);//static_cast<std::string>(item.first);
            firstpos = firstpos + ";";
            firstpos = firstpos + item.second;
            firstpos = firstpos + ")";
        }
        firstpos = firstpos + "}";
        nodes[i]->info.firstpos.setFont(font); // font is a sf::Font
        nodes[i]->info.firstpos.setCharacterSize(15); // in pixels, not points!
        nodes[i]->info.firstpos.setPosition(sf::Vector2(nodes[i]->coords.x + 20.0f, nodes[i]->coords.y - 20.0f));
        nodes[i]->info.firstpos.setString(firstpos);
        nodes[i]->info.firstpos.setFillColor(sf::Color::White);

        std::string lastpos = "{";
        for (auto item : nodes[i]->data->value.lastpos)
        {
            lastpos = lastpos + "(";
            /////////////////////////////////////////////////////////////
            lastpos = lastpos + std::to_string(item.first);//static_cast<std::string>(item.first);
            lastpos = lastpos + ";";
            lastpos = lastpos + item.second;
            lastpos = lastpos + ")";
        }
        lastpos = lastpos + "}";
        nodes[i]->info.lastpos.setFont(font); // font is a sf::Font
        nodes[i]->info.lastpos.setCharacterSize(15); // in pixels, not points!
        nodes[i]->info.lastpos.setPosition(sf::Vector2(nodes[i]->coords.x + 20.0f, nodes[i]->coords.y + 20.0f));
        nodes[i]->info.lastpos.setString(lastpos);
        nodes[i]->info.lastpos.setFillColor(sf::Color::White);

        switch (nodes[i]->data->value.type)
        {
            case NData::Type::Char:
            {
                nodes[i]->circle.setOutlineColor(sf::Color::White);
                // set the string to display
                nodes[i]->info.text.setString(nodes[i]->data->value.firstpos.begin()->second);
                // set the color
                nodes[i]->info.text.setFillColor(sf::Color::Black);
                break;
            }
            case NData::Type::Conc:
            {
                nodes[i]->circle.setOutlineColor(sf::Color::Red);
                // set the string to display
                nodes[i]->info.text.setString("&");
                // set the color
                nodes[i]->info.text.setFillColor(sf::Color::Red);
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
                // set the string to display
                nodes[i]->info.text.setString("+");
                // set the color
                nodes[i]->info.text.setFillColor(sf::Color::Blue);
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
                nodes[i]->info.text.setString("*");
                nodes[i]->info.text.setFillColor(sf::Color::Green);
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
}

void drawtree(std::shared_ptr<Node<NData>> root)
{
    sf::View view; // Окно просмотра.
    sf::RenderWindow window; //создается окно
    sf::ContextSettings context; //какие-то связанные настройки

    context.antialiasingLevel = 0;
    context.depthBits = 24;
    context.stencilBits = 8;
    context.majorVersion = 3;
    context.minorVersion = 0;

    int scale_base = 2; //изменение масштаба
    int scale_power = 0; //изменение масштаба

    tgui::Gui gui{window};
    //std::cout << "You have a GUI!" << std::endl;

    sf::Font font;
    if (!font.loadFromFile("../../SourceCodePro-Regular.otf"))
    {
        std::cout << "ERROR!!!" << std::endl;
    }

    window.create(sf::VideoMode(800, 600)/*ширина, высота*/, "Rubbur"/*имя окна*/, sf::Style::Default, context); // Создание окна.
    window.setFramerateLimit(60); // Ограничение на частоту обновления экрана.

    view.setCenter(0.0f, 0.0f); //координаты центра экрана
    view.setSize(static_cast<sf::Vector2f>(window.getSize())); //чтобы отображалась область, совпадающую с экраном
    view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f)); //все, что показывает view, будет на экране
    window.setView(view); //задается камера окну
    gui.setView(view);

    /*На глубине h запишем место для 2^h вершин; т.е. они будут на расстоянии 50*2^(root.depth - h) друг от друга*/
    std::vector<std::shared_ptr<Node<NData>>> tree;
    depthsearch(tree, root);

    std::vector<std::shared_ptr<GRExpNode>> nodes;
    std::unordered_map<Node<NData>*, std::shared_ptr<GRExpNode>> table;
    makegvec(tree, nodes, table);

    float minx = 0;
    float maxx = 0;
    float miny = 0;
    float maxy = 0;

    std::pair<float,float> sizes;
    makegr(table[root.get()], table, sizes, minx, maxx, miny, maxy);
    makenodes(nodes, font);

    auto button = tgui::Button::create();
    button->setPosition(-110, -60);
    button->setText("See all");
    button->setSize(100, 30);
    button->connect("pressed", sig_button, std::ref(window), std::ref(gui), std::ref(view), std::ref(sizes), std::ref(scale_base), std::ref(scale_power));
    gui.add(button);
    //std::cout << "You have a button!" << std::endl;

    bool see_info = false;

    auto see_info_but = tgui::Button::create();
    see_info_but->setPosition(10, -60);
    see_info_but->setText("See info");
    see_info_but->setSize(100, 30);
    see_info_but->connect("pressed", sig_see_info_but, std::ref(see_info), std::ref(*(see_info_but)));
    gui.add(see_info_but);

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
                    gui.setView(view);
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
                        case sf::Keyboard::Enter: //какая-то клавиша
                        {
                            window.close();
                            break;
                        }
                        case sf::Keyboard::Escape: //какая-то клавиша
                        {
                            window.close();
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window.hasFocus()) //зажатая клавиша мыши
        {
            sf::Vector2f new_mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            view.move(mouse_position - new_mouse_position);
            window.setView(view);
            gui.setView(view);
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
            window.draw(nodes[i]->info.text);
            if(see_info == true)
            {
                window.draw(nodes[i]->info.nullable);
                window.draw(nodes[i]->info.firstpos);
                window.draw(nodes[i]->info.lastpos);
            }
        }

        gui.draw();
        //window.draw(circle);
        window.display();
    }
}
