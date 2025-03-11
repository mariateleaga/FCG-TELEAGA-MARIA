////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

////////////////////////////////////////////////////////////
/// GUI State
const int FONT_SIZE = 24; 
const int FONT_WIDTH = 14;
const std :: string FONT_NAME="../src/Resources/DejavuSansMono-5m7L.ttf";
struct State
{
    // General resources
    sf::RenderWindow window;
    const sf::Font font{FONT_NAME};
    // Text buffer
    std::vector<std::string> log;
    sf::IntRect text_view;
    sf::Vector2i cursor_pos;

    State(unsigned w, unsigned h, std::string title)
    {
        window = sf::RenderWindow(sf::VideoMode({w, h}), title);
        // window.setVerticalSyncEnabled(true); // alternative to setFramerateLimit
        window.setFramerateLimit(60);
        log.resize(1, "");
        text_view = {{0, 0}, {static_cast<int>(w / FONT_WIDTH - 2), static_cast<int> (h / FONT_SIZE - 2)}};
        cursor_pos = {0, 0};
    }

    /*void adjustView() //questo sicuramente non è proprio così non so come l'ha dichiarata lui, da rivedere VIRGI
    {
       text_view.size = {static_cast<int>(window.getSize().x / FONT_WIDTH - 2), static_cast<int> (window.getSize().y / FONT_SIZE - 2)}; //è un vector
    //cambio il punto di ancoraggio per quando scappa il cursore VIRGI
       text_view.position.x = std::min(text_view.positioin.x, cursor_pos.x);
       text_view.position.x = std::max(text_view.positioin.x, cursor_pos.x - text_view.size.x + 1);
       text_view.position.y = std::min(text_view.positioin.y, cursor_pos.y);
       text_view.position.y = std::max(text_view.positioin.y, cursor_pos.y - text_view.size.y + 1);
    }*/
};
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// Callback functions
void handle(const sf::Event::Closed &, State &gs)
{
    gs.window.close();
}

void handle(const sf::Event::TextEntered &textEnter, State &gs)
{
    unsigned last = gs.log.size() - 1;
    // if (textEnter.unicode == 10 || textEnter.unicode == 13)
    if (textEnter.unicode == '\n' || textEnter.unicode == '\r') // enter
    {
        gs.log.emplace_back("");
        //spostiamo le coordinate cursore VIRGI
        gs.cursor_pos = {0, gs.cursor_pos.y+1}; //se vado a capo lo porto alla colonna 0 ma riga successiva
    }
    else if (textEnter.unicode >= ' ' && textEnter.unicode <= '~') // printable char
    {
        gs.log[last] += static_cast<char>(textEnter.unicode);
        gs.cursor_pos.x++; //altrimenti avanziamo di una colonna
    }

    
    void adjustView(); //aggiusta la vista tutte le volte che intervengono azioni che possono cambiarla VIRGI
}

// void handle(const sf::Event::KeyPressed &keyPressed, State &gs)
// {
// }

// void handle(const sf::Event::MouseMoved &mouseMoved, State &gs)
// {
// }

// void handle(const sf::Event::MouseButtonPressed &, State &gs)
// {
// }

void handle(const sf::Event::Resized &resized, State &gs)
{
    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized.size));
    gs.window.setView(sf::View(visibleArea));
    gs.adjustView(); //VIRGI
}

template <typename T>
void handle(const T &, State &gs)
{
    // All unhandled events will end up here
}
///
////////////////////////////////////////////////////////////
void doGraphics(State &gs) //codice tolto dal main che si occupa solo della parte grafica
{
    sf::Text logText{gs.font, "", FONT_SIZE};
    // Show text in view //VIRGI
    unsigned lines_to_print 0 std::min(static_cast<unsigned>(gs.log.size() - gs.text_view.position.y),
    static_cast<unsigned>(gs.text_view.size.y));

        gs.window.clear();
        //CANCELLIAMO QUESTE DUE RIGHE
        //if (gs.log.size() > 24u) // Limit the log to the last 24 entries
            //gs.log.erase(gs.log.begin(), gs.log.begin() + static_cast<int>(gs.log.size() - 24u));
        for (std::size_t i = 0; i < gs.log.size(); ++i)
        {
            logText.setPosition({FONT_WIDTH, static_cast<float>(i * FONT_SIZE) + FONT_SIZE}); //dopo il + lascio l'altezza e la larghezza di un carattere
            logText.setString(gs.log[i]);
            gs.window.draw(logText);
        }
        // Show cursors, quando ti chiederò di disegnare text disegna un underscore e disegnalo verde
        logText.setString("_"); //gli dico cosa va disegnato
        logText.setFillColor(sf::Color::Green); //assegno il colore verde VIRGI
        logText.setPosition({static_cast<float>(gs.cursor_pos.x - gs.text_view.position.x+ 1) * FONT_WIDTH, 
                             static_cast<float>(gs.cursor_pos.y - gs.text_view.position.y+ 1) * FONT_SIZE+ 3}); //gli diciamo dove disegnarlo
        gs.window.draw(logText); //gli dico di disegnarlo effettivamente
        gs.window.display();
}


int main()
{
    State gs(800, 600, "Text echo");
    sf::Text logText{gs.font, "", FONT_SIZE};
    while (gs.window.isOpen()) // main loop
    {
        // event loop and handler through callbacks
        gs.window.handleEvents([&](const auto &event)
                               { handle(event, gs); });
        
        doGraphics(gs);             
    }
}