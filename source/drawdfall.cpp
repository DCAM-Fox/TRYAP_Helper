#include "drawdfall.hpp"
//#include "messagequeue.hpp"

//#define DEBUG_DRAWDFA

void sig_see_tree(sf::RenderWindow & window, tgui::Gui & gui, sf::View & view, std::pair<float, float>& sizes, int scale_base, int & scale_power)
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

void if_draw_aut(bool & draw_aut, bool & draw_tree, bool & draw_fp)
{
    draw_aut = true;
    draw_tree = false;
    draw_fp = false;
}

void if_draw_tree(bool & draw_aut, bool & draw_tree, bool & draw_fp)
{
    draw_aut = false;
    draw_tree = true;
    draw_fp = false;
}

void if_draw_fp(bool & draw_aut, bool & draw_tree, bool & draw_fp)
{
    draw_aut = false;
    draw_tree = false;
    draw_fp = true;
}

std::string drawdfall(DFA& dfa, std::shared_ptr<Node<NData>> root, std::vector<std::set<std::pair<size_t, char>>>& followpos, std::shared_ptr<mtt::Messaging<TurnOn>> turn_on_box, std::shared_ptr<mtt::Messaging<GetWord>> get_word_box)//, std::string& the_word)
{
    sf::View view; // Окно просмотра.
    sf::RenderWindow window; //создается окно
    sf::ContextSettings context; //какие-то связанные настройки
    tgui::Gui gui{window};

    int scale_base = 2; //изменение масштаба
    int scale_power = 0; //изменение масштаба

    window.create(sf::VideoMode(800, 600)/*ширина, высота*/, "Rubbur"/*имя окна*/, sf::Style::Default, context); // Создание окна.
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

    ////TREE////
    /*На глубине h запишем место для 2^h вершин; т.е. они будут на расстоянии 50*2^(root.depth - h) друг от друга*/
    std::vector<std::shared_ptr<Node<NData>>> tree;
    depthsearch(tree, root);

    std::vector<std::shared_ptr<GRExpNode>> nodes;
    std::unordered_map<Node<NData>*, std::shared_ptr<GRExpNode>> tabletree;
    makegvec(tree, nodes, tabletree);

    float minx = 0;
    float maxx = 0;
    float miny = 0;
    float maxy = 0;

    std::pair<float,float> sizes;
    makegr(tabletree[root.get()], tabletree, sizes, minx, maxx, miny, maxy);
    makenodes(nodes, font);

    bool is_sat = false;
    auto see_all_tree = tgui::Button::create();
    see_all_tree->setPosition(-110, -60);
    see_all_tree->setText("See all");
    see_all_tree->setSize(100, 30);
    see_all_tree->connect("pressed", sig_see_tree, std::ref(window), std::ref(gui), std::ref(view), std::ref(sizes), std::ref(scale_base), std::ref(scale_power));
    //gui.add(see_all_tree);
    //std::cout << "You have a button!" << std::endl;

    bool see_info = false;

    bool is_sib = false;
    auto see_info_but = tgui::Button::create();
    see_info_but->setPosition(10, -60);
    see_info_but->setText("See info");
    see_info_but->setSize(100, 30);
    see_info_but->connect("pressed", sig_see_info_but, std::ref(see_info), std::ref(*(see_info_but)));
    //gui.add(see_info_but);

    ////AUTOMATA////
    bool is_checking = false;
    size_t current_state = 0;
    std::string the_word;

    std::vector<std::shared_ptr<DFState>> automata;
    std::vector<std::shared_ptr<GState>> gstates;
    std::unordered_map<DFState*, std::shared_ptr<GState>> tableaut;
    std::vector<std::shared_ptr<GArrow>> arrows;
    std::vector<std::shared_ptr<GArrowHead>> heads;
    std::vector<sf::Text> text;

    sf::Text str1;
    str1.setFont(font); // font is a sf::Font
    str1.setString("");
    str1.setCharacterSize(20); // in pixels, not points!
    str1.setFillColor(sf::Color::Red);
    str1.setPosition(-300,35);
    sf::Text str2;
    str2.setFont(font); // font is a sf::Font
    str2.setString("");
    str2.setCharacterSize(20); // in pixels, not points!
    str2.setFillColor(sf::Color::Red);
    str2.setPosition(-300,75);
    sf::Text str3;
    str3.setFont(font); // font is a sf::Font
    str3.setString("");
    str3.setCharacterSize(20); // in pixels, not points!
    str3.setFillColor(sf::Color::Red);
    str3.setPosition(-300,110);

    makeaut(dfa, automata);

    makebase(automata, gstates, tableaut);

    makelayout(gstates, text, font);

    makearrows(dfa, gstates, arrows, font);

    bool is_eb = false;
    auto editBox = tgui::EditBox::create();
    //editBox->setRenderer(theme.getRenderer("EditBox"));
    editBox->setSize(250, 30);
    editBox->setTextSize(20);
    editBox->setPosition(-300, -35);
    editBox->setDefaultText("More automatas? y/n");
    //gui.add(editBox);

    bool is_wb = false;
    auto wordBox = tgui::EditBox::create();
    //editBox->setRenderer(theme.getRenderer("EditBox"));
    wordBox->setSize(250, 30);
    wordBox->setTextSize(20);
    wordBox->setPosition(-300, 0);
    wordBox->setDefaultText("Put the word to check!");
    wordBox->connect("ReturnKeyPressed", sig_word, std::ref(get_word_box), std::ref(wordBox), std::ref(is_checking), std::ref(the_word), std::ref(current_state), std::ref(gstates));
    //gui.add(wordBox);

    ////FOLLOWPOS////
    sf::Text greetingp;
    greetingp.setFont(font); // font is a sf::Font
    greetingp.setString("FOLLOWPOS");
    greetingp.setCharacterSize(50); // in pixels, not points!
    greetingp.setFillColor(sf::Color::Red);
    greetingp.setPosition(0,0);

    //std::cout << "Greeting" << std::endl;

    std::vector<sf::Text> poses;
    sf::Text posi;
    std::string pos;

    for(size_t i = 0; i < followpos.size(); ++i)
    {
        pos = std::to_string(i);
        pos = pos + ": {";
        for(auto item : followpos[i])
        {
            pos = pos + "(";
            pos = pos + std::to_string(item.first);
            pos = pos + ";";
            pos = pos + item.second;
            pos = pos + ")";
        }
        pos = pos + "}";
        posi.setFont(font);
        posi.setCharacterSize(30);
        posi.setFillColor(sf::Color::Red);
        posi.setPosition(0,(60 + 30*i));
        posi.setString(pos);
        poses.push_back(posi);
    }

    //WHAT TO DO//
    bool draw_aut = true;
    bool draw_tree = false;
    bool draw_fp = false;

    bool is_dab = false;
    auto draw_aut_but = tgui::Button::create();
    draw_aut_but->setPosition(-50, -100);
    draw_aut_but->setText("AUTOMATA");
    draw_aut_but->setSize(100, 30);
    draw_aut_but->connect("pressed", if_draw_aut, std::ref(draw_aut), std::ref(draw_tree), std::ref(draw_fp));
    //gui.add(draw_aut_but);

    bool is_dtb = false;
    auto draw_tree_but = tgui::Button::create();
    draw_tree_but->setPosition(-425, 0);
    draw_tree_but->setText("TREE");
    draw_tree_but->setSize(100, 30);
    draw_tree_but->connect("pressed", if_draw_tree, std::ref(draw_aut), std::ref(draw_tree), std::ref(draw_fp));
    //gui.add(draw_aut_but);

    bool is_dfb = false;
    auto draw_fp_but = tgui::Button::create();
    draw_fp_but->setPosition(-425, -35);
    draw_fp_but->setText("FOLLOWPOS");
    draw_fp_but->setSize(100, 30);
    draw_fp_but->connect("pressed", if_draw_fp, std::ref(draw_aut), std::ref(draw_tree), std::ref(draw_fp));
    //gui.add(draw_aut_but);

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
                    GetWord msg;
                    msg.word = "";
                    msg.should_stop = true;
                    get_word_box->send(msg);
                    #ifdef DEBUG_DRAWDFA
                    std::cout << "msg SENT" << std::endl;
                    #endif
                    return "closed";
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
                        ///////
                        case sf::Keyboard::Escape:
                        {
                            GetWord msg;
                            msg.word = "";
                            msg.should_stop = true;
                            get_word_box->send(msg);
                            #ifdef DEBUG_DRAWDFA
                            std::cout << "msg SENT" << std::endl;
                            #endif
                            window.close();
                            return "closed";
                            break;
                        }
                        case sf::Keyboard::Enter: //какая-то клавиша
                        {
                            const sf::String& more_auts = editBox->getText();
                            //const sf::String& wword = wordBox->getText();
                            std::string more = more_auts;
                            //std::string word = wword;
                            std::cout << more << std::endl;
                            //std::cout << word << std::endl;
                            //str = in_put;
                            if((more == "Yes") || (more == "yes") || (more == "Y") || (more == "y"))
                            {
                                GetWord msg;
                                msg.word = "";
                                msg.should_stop = true;
                                get_word_box->send(msg);
                                #ifdef DEBUG_DRAWDFA
                                std::cout << "msg SENT" << std::endl;
                                #endif
                                window.close();
                                return "yes";
                            }
                            else
                            {
                                if((more == "No") || (more == "no") || (more == "N") || (more == "n"))
                                {
                                    GetWord msg;
                                    msg.word = "";
                                    msg.should_stop = true;
                                    get_word_box->send(msg);
                                    #ifdef DEBUG_DRAWDFA
                                    std::cout << "msg SENT" << std::endl;
                                    #endif
                                    window.close();
                                    return "no";
                                }
                                else
                                {
                                    editBox->setText("");
                                }
                            }
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

        if(draw_aut == true)
        {
            //std::cout<<"A"<<std::endl;
            if(is_eb == false)
            {
                gui.add(editBox);
                is_eb = true;
            }
            if(is_wb == false)
            {
                gui.add(wordBox);
                is_wb = true;
            }
            draw_tree_but->setPosition(-425, 0);
            if(is_dtb == false)
            {
                gui.add(draw_tree_but);
                is_dtb = true;
            }
            draw_fp_but->setPosition(-425, -35);
            if(is_dfb == false)
            {
                gui.add(draw_fp_but);
                is_dfb = true;
            }
            if(is_sat == true)
            {
                gui.remove(see_all_tree);
                is_sat = false;
            }
            if(is_sib == true)
            {
                gui.remove(see_info_but);
                is_sib = false;
            }
            if(is_dab == true)
            {
                gui.remove(draw_aut_but);
                is_dab = false;
            }
        }
        if(draw_tree == true)
        {
            if(is_eb == true)
            {
                gui.remove(editBox);
                is_eb = false;
            }
            if(is_wb == true)
            {
                gui.remove(wordBox);
                is_wb = false;
            }
            if(is_dtb == true)
            {
                gui.remove(draw_tree_but);
                is_dtb = false;
            }
            if(is_sat == false)
            {
                gui.add(see_all_tree);
                is_sat = true;
            }
            if(is_sib == false)
            {
                gui.add(see_info_but);
                is_sib = true;
            }
            draw_aut_but->setPosition(-110, -100);
            if(is_dab == false)
            {
                gui.add(draw_aut_but);
                is_dab = true;
            }
            draw_fp_but->setPosition(10, -100);
            if(is_dfb == false)
            {
                gui.add(draw_fp_but);
                is_dfb = true;
            }
        }
        if(draw_fp == true)
        {
            if(is_eb == true)
            {
                gui.remove(editBox);
                is_eb = false;
            }
            if(is_wb == true)
            {
                gui.remove(wordBox);
                is_wb = false;
            }
            if(is_dfb == true)
            {
                gui.remove(draw_fp_but);
                is_dfb = false;
            }
            if(is_sat == true)
            {
                gui.remove(see_all_tree);
                is_sat = false;
            }
            if(is_sib == true)
            {
                gui.remove(see_info_but);
                is_sib = false;
            }
            draw_tree_but->setPosition(10, -100);
            if(is_dtb == false)
            {
                gui.add(draw_tree_but);
                is_dtb = true;
            }
            draw_aut_but->setPosition(-110, -100);
            if(is_dab == false)
            {
                gui.add(draw_aut_but);
                is_dab = true;
            }
        }

        window.clear(sf::Color::Black); //очистить экран

        if(draw_aut == true)
        {
            if(is_checking == true)
            {
                #ifdef DEBUG_DRAWDFA
                std::cout << current_state << std::endl;
                #endif
                if ((current_state == 0) && (gstates[current_state]->circle.getFillColor() == sf::Color::White))
                {
                    gstates[current_state]->circle.setFillColor(sf::Color::Yellow);
                }
                str1.setString("Your word");
                str2.setString(the_word);
                TurnOn should_turn_on;
                if(turn_on_box->try_receive(should_turn_on))
                {
                    #ifdef DEBUG_DRAWDFA
                    std::cout << current_state << std::endl;
                    #endif

                    if(should_turn_on.is_wrong == false)
                    {
                        if(should_turn_on.state_number == current_state)
                        {
                            if (gstates[current_state]->circle.getFillColor() == sf::Color::Yellow)
                            {
                                gstates[should_turn_on.state_number]->circle.setFillColor(sf::Color::Cyan);
                            }
                            else
                            {
                                gstates[should_turn_on.state_number]->circle.setFillColor(sf::Color::Yellow);
                            }
                        }
                        else
                        {
                            gstates[should_turn_on.state_number]->circle.setFillColor(sf::Color::Yellow);
                            gstates[current_state]->circle.setFillColor(sf::Color::White);
                        }
                        current_state = should_turn_on.state_number;
                        if(should_turn_on.is_all == true)
                        {
                            if(dfa.states[should_turn_on.state_number]->is_accepting == true)
                            {
                                str3.setString("IS ACCEPTED");
                                #ifdef DEBUG_DRAWDFA
                                std::cout << "ACCEPTED" << std::endl;
                                #endif
                            }
                            else
                            {
                                str3.setString("IS REJECTED");
                                #ifdef DEBUG_DRAWDFA
                                std::cout << "NOT ACCEPTED" << std::endl;
                                #endif
                            }
                        }
                        else
                        {
                            str3.setString("IS BEING CHECKED");
                        }
                    }
                    else
                    {
                        str3.setString("IS REJECTED");
                    }
                }
            }

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
            window.draw(str1);
            window.draw(str2);
            window.draw(str3);
        }
        if((draw_tree == true) && (draw_aut == false))
        {
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
        }
        if(draw_fp == true)
        {
            window.draw(greetingp);
            for(size_t i = 0; i < followpos.size(); ++i)
            {
                window.draw(poses[i]);
            }
        }
        gui.draw();

        window.display();

        //std::cout << "w";
    }
    return "nothing";
}
