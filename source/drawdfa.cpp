#include "drawdfa.hpp"
#include <TGUI/TGUI.hpp>

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
        gstates[i]->coords.x = 100*i;
        gstates[i]->coords.y = 0;

        #ifdef DEBUG_DRAWDFA
        std::cout << "i = " << i << "; coords: (" << gstates[i]->coords.x << ";" << gstates[i]->coords.y << ")" << std::endl;
        #endif
    }
}

void makearrows(DFA& dfa, std::vector<std::shared_ptr<GState>>& gstates, std::vector<std::shared_ptr<GArrow>>& arrows, sf::Font& font)//, std::vector<std::vector<std::shared_ptr<sf::Text>>>& arrowtext)
{
    for(size_t i = 0; i < gstates.size(); ++i)
    {
        arrows.push_back(std::make_shared<GArrow>());
    }
    std::vector<size_t> counts;
    for(size_t i = 0; i < gstates.size(); ++i)
    {
        for(size_t j = 0; j < gstates.size(); ++j)
        {
            counts.push_back(0);
        }
        //arrowtext.push_back(std::vector<std::shared_ptr<sf::Text>>());
        for(size_t c = 0; c < 256; ++c)
        {
            for(size_t j = 0; j < gstates.size(); ++j)
            {
                char ch = static_cast<char>(c);
                if ((dfa.transit[256*i + c] >= 0) && (static_cast<size_t>(dfa.transit[256*i + c]) == j))
                {
                    arrows[i]->lines.push_back(std::array<sf::Vertex, 2>());
                    arrows[i]->lines.push_back(std::array<sf::Vertex, 2>());
                    arrows[i]->lines.push_back(std::array<sf::Vertex, 2>());

                    arrows[i]->heads.push_back(GArrowHead());

                    sf::Text arrowtext;

                    arrowtext.setFont(font); // font is a sf::Font
                    arrowtext.setString(std::string(1, ch)); // std::to_string(ch));
                    arrowtext.setCharacterSize(15); // in pixels, not points!
                    arrowtext.setFillColor(sf::Color::Red);

                    //size_t tsize = arrows[i]->text.size();

                    arrows[i]->text.push_back(arrowtext);

                    size_t lsize = arrows[i]->lines.size();
                    ssize_t delta = gstates[j]->coords.x - gstates[i]->coords.x;

                    if((delta != 0) && (delta != 100))
                    {
                        arrows[i]->lines[lsize-3][0] = sf::Vertex(gstates[i]->coords);
                        arrows[i]->lines[lsize-3][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x,
                                                                               gstates[i]->coords.y - abs(delta/5) - 20.0f));
                        arrows[i]->lines[lsize-2][0] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x,
                                                                               gstates[i]->coords.y - abs(delta/5) - 20.0f));
                        arrows[i]->lines[lsize-2][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x + (abs(delta) - 20.0f)*(abs(delta)/delta),
                                                                               gstates[i]->coords.y - abs(delta/5) - 20.0f));
                        arrows[i]->lines[lsize-1][0] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x + (abs(delta) - 20.0f)*(abs(delta)/delta),
                                                                               gstates[i]->coords.y - abs(delta/5) - 20.0f));
                        arrows[i]->lines[lsize-1][1] = sf::Vertex({gstates[i]->coords.x + delta,
                                gstates[i]->coords.y}); //same as sf vector

                        size_t hsize = arrows[i]->heads.size();
                        arrows[i]->heads[hsize-1].setOrigin(-20.0, 0);
                        arrows[i]->heads[hsize-1].setPosition(gstates[j]->coords);
                        double angle = (180/M_PI)*atan2((arrows[i]->lines[lsize-1][0].position.x - arrows[i]->lines[lsize-1][1].position.x), (arrows[i]->lines[lsize-1][0].position.y - arrows[i]->lines[lsize-1][1].position.y));
                        arrows[i]->heads[hsize-1].setRotation(-angle+90.0f);
                    }
                    else
                    {
                        if(delta == 0)
                        {
                            arrows[i]->lines[lsize-3][0] = sf::Vertex(gstates[i]->coords);
                            arrows[i]->lines[lsize-3][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x - 20.0f,
                                                                                   gstates[i]->coords.y + 40.0f));
                            arrows[i]->lines[lsize-2][0] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x - 20.0f,
                                                                                   gstates[i]->coords.y + 40.0f));
                            arrows[i]->lines[lsize-2][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x + 20.0f,
                                                                                   gstates[i]->coords.y + 40.0f));
                            arrows[i]->lines[lsize-1][0] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x + 20.0f,
                                                                                   gstates[i]->coords.y + 40.0f));
                            arrows[i]->lines[lsize-1][1] = sf::Vertex(gstates[i]->coords);

                            size_t hsize = arrows[i]->heads.size();
                            arrows[i]->heads[hsize-1].setOrigin(-20.0, 0);
                            arrows[i]->heads[hsize-1].setPosition(gstates[j]->coords);
                            arrows[i]->heads[hsize-1].setRotation((180/M_PI)*atan(40/20));
                        }
                        else
                        {
                            if(delta == 100)
                            {
                                arrows[i]->lines[lsize-3][0] = sf::Vertex(gstates[i]->coords);
                                arrows[i]->lines[lsize-3][1] = sf::Vertex(gstates[i]->coords);
                                arrows[i]->lines[lsize-2][0] = sf::Vertex(gstates[i]->coords);
                                arrows[i]->lines[lsize-2][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x + delta,
                                                                                       gstates[i]->coords.y));
                                arrows[i]->lines[lsize-1][0] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x + delta,
                                                                                       gstates[i]->coords.y));
                                arrows[i]->lines[lsize-1][1] = sf::Vertex(sf::Vector2f(gstates[i]->coords.x + delta,
                                                                                       gstates[i]->coords.y));

                                size_t hsize = arrows[i]->heads.size();
                                arrows[i]->heads[hsize-1].setOrigin(-20.0, 0);
                                arrows[i]->heads[hsize-1].setPosition(gstates[j]->coords);
                                arrows[i]->heads[hsize-1].setRotation(180.0f);
                            }
                        }
                    }
                    arrows[i]->text[arrows[i]->text.size() - 1].setPosition((((arrows[i]->lines[lsize-2][0].position.x + arrows[i]->lines[lsize-2][1].position.x)/2)+20*counts[i * gstates.size() + j]), (arrows[i]->lines[lsize-2][0].position.y + arrows[i]->lines[lsize-2][1].position.y)/2);
                    ++counts[i*gstates.size() + j];
                }
            }
        }
    }
}

void drawdfa(DFA& dfa)
{
    sf::View view; // Окно просмотра.
    sf::RenderWindow window; //создается окно
    sf::ContextSettings context; //какие-то связанные настройки
    /*
    ////////////////
    tgui::Gui gui{window};

    auto editBox = tgui::EditBox::create();
    //editBox->setRenderer(theme.getRenderer("EditBox"));
    editBox->setSize(300, 30);
    editBox->setTextSize(20);
    editBox->setPosition(10, 270);
    editBox->setDefaultText("Click to edit text...");
    gui.add(editBox);
    //////////////////////
    */

    int scale_base = 2; //изменение масштаба
    int scale_power = 0; //изменение масштаба

    window.create(sf::VideoMode(600, 400)/*ширина, высота*/, "Rubbur"/*имя окна*/, sf::Style::Default, context); // Создание окна.
    window.setFramerateLimit(60); // Ограничение на частоту обновления экрана.

    view.setCenter(0.0f, 0.0f); //координаты центра экрана
    view.setSize(static_cast<sf::Vector2f>(window.getSize())); //чтобы отображалась область, совпадающую с экраном
    view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f)); //все, что показывает view, будет на экране
    window.setView(view); //задается камера окну

    std::vector<std::shared_ptr<DFState>> automata;
    std::vector<std::shared_ptr<GState>> gstates;
    std::unordered_map<DFState*, std::shared_ptr<GState>> table;
    std::vector<std::shared_ptr<GArrow>> arrows;
    std::vector<std::shared_ptr<GArrowHead>> heads;

    sf::Font font;
    if (!font.loadFromFile("../../SourceCodePro-Regular.otf"))
    {
        std::cout << "ERROR!!!" << std::endl;
    }

    std::vector<sf::Text> text;
    //std::vector<std::shared_ptr<sf::Text>> text;
    //    std::vector<std::vector<std::shared_ptr<sf::Text>>> arrowtext;

    makeaut(dfa, automata);

    makebase(automata, gstates, table);

    makelayout(gstates);

    makearrows(dfa, gstates, arrows, font);

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
    }

    for(size_t i = 0; i < gstates.size(); ++i)
    {
        text.push_back(sf::Text());
        // select the font
        text[i].setFont(font); // font is a sf::Font

        // set the string to display
        text[i].setString(std::to_string(i));

        // set the character size
        text[i].setCharacterSize(20); // in pixels, not points!

        // set the color
        text[i].setFillColor(sf::Color::Red);
        text[i].setPosition(sf::Vector2(gstates[i]->coords.x - 5.0f, gstates[i]->coords.y - 15.0f));
    }

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
            //gui.handleEvent(window_event);
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
            //рисование линий
            for (size_t j = 0; j < arrows[i]->lines.size(); ++j)
            {
                window.draw(arrows[i]->lines[j].data(), 2, sf::Lines);
            }
            for(size_t j = 0; j < arrows[i]->heads.size(); ++j)
            {
                window.draw(arrows[i]->heads[j]);
            }
            for(size_t j = 0; j < arrows[i]->text.size(); ++j)
            {
                window.draw(arrows[i]->text[j]);
            }
        }
        for(size_t i = 0; i < gstates.size(); ++i)
        {
            #ifdef DEBUG_DRAWDFA
            std::cout << i << ": circle: (" << gstates[i]->coords.x << ";" << gstates[i]->coords.y << "), ring: "<< gstates[i]->ring.getRadius() << std::endl;
            #endif
            window.draw(gstates[i]->circle);
            window.draw(gstates[i]->ring);

            window.draw(text[i]);
        }
        //window.draw(text);
        //gui.draw();

        //window.draw(circle);
        window.display();
    }
}
