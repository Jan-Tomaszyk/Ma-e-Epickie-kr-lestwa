#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <cmath>

using namespace std; using namespace sf;

struct Node {
    sf::CircleShape shape;
    sf::Vector2f position;
    bool selected = false;
};

struct Pawn {
    sf::RectangleShape shape;
    sf::Vector2f position;
    Node* current_node = nullptr;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Game");

    // Setup nodes
    vector<Node> nodes;
    map<int, std::vector<int>> adjacency_list = {
        {0, {1, 2}},
        {1, {0, 2}},
        {2, {0, 1}}
    };

    // Create nodes
    for (int i = 0; i < 3; ++i)
    {
        Node node;
        node.position = sf::Vector2f(200 + i * 200, 300+(50*int(pow(-1.0,double(i)))));
        node.shape.setRadius(30);
        node.shape.setFillColor(sf::Color::Blue);//miejsce do ustawienia koloru
        node.shape.setPosition(node.position);
        nodes.push_back(node);
    }

    // Create pawns
    vector <Pawn> pawns;
    vector <bool> pawn_selected;
    for (int i = 0; i < 2; ++i)
    {
        Pawn pawn;
        pawn.shape.setSize(sf::Vector2f(20, 20));
        pawn.shape.setFillColor(sf::Color::Red);//miejsce do ustawienia koloru
        pawn.shape.setPosition(nodes[i].position);
        pawn.current_node = &nodes[i];
        pawns.push_back(pawn);
        pawn_selected.push_back(false);
    }
    // Mouse input
    sf::Vector2i mouse_pos;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        mouse_pos = sf::Mouse::getPosition(window);

        // Check for node click
        for (int i=0; i<pawns.size(); ++i)
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (pawns[i].shape.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                    {
                        if (!pawn_selected[i])
                        {
                            // Select pawn
                            pawn_selected[i] = true;
                        }
                    }
                }
            }
        }
        for (int i=0; i<pawns.size(); ++i)
        {
        for (auto& node : nodes)
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (node.shape.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
                    {
                        if (pawn_selected[i])
                        {
                            // Check if adjacent
                            bool is_adjacent = false;
                            for (int neighbor : adjacency_list[pawns[i].current_node - &nodes[0]])
                            {
                                if (&nodes[neighbor] == &node)
                                {
                                    is_adjacent = true;
                                    break;
                                }
                            }
                            if (is_adjacent)
                            {
                                pawns[i].shape.setPosition(node.position);
                                pawns[i].current_node = &node;
                                pawn_selected[i] = false;
                            }
                        }
                    }
                }
            }
        }
        }
        // Set shape origins to centers *before* positioning:
        for (auto& node : nodes)
        {
            node.shape.setOrigin(
                node.shape.getRadius(),
                node.shape.getRadius()
            );
        }

        // Then update all node positions:
        for (auto& node : nodes)
        {
            node.shape.setPosition(node.position);
        }
        // Draw
        sf::VertexArray edges(sf::Lines);
        for (const auto& [node_idx, neighbors] : adjacency_list)
        {
            for (int neighbor : neighbors)
            {
                sf::Vector2f dir = nodes[neighbor].position - nodes[node_idx].position;
                double length = sqrt(dir.x*dir.x + dir.y*dir.y);
                if (length > 0) //normalizacja bez dzielenia przez 0
                {
                    dir.x /= length;
                    dir.y /= length;
                }
                sf::Vector2f offset = dir * nodes[node_idx].shape.getRadius();

                edges.append(sf::Vertex(nodes[node_idx].position+offset, sf::Color::White));
                edges.append(sf::Vertex(nodes[neighbor].position-offset, sf::Color::White));
            }
        }
        window.clear();
        for (auto& node : nodes)
        {
            window.draw(node.shape);
        }
        window.draw(edges);
        window.draw(pawns[0].shape);
        window.draw(pawns[1].shape);
        window.display();
    }

    return 0;
}
