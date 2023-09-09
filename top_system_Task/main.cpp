/*It is necessary to provide an example of a program or library in C++ that displays various
geometric shapes: circle, square, triangle, rectangle, etc. Depth of elaboration of the example
(number of figures, parameters, methods) at your discretion. The program does not have to be up and running (although this would be a plus).
In the assignment you need to demonstrate your ability to use OOP. Please do not use the QT library when completing this task.*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

//! Main characteristics of the shapes
class Shape
{
    //! Declaring friend classes for access to private data
    friend class Circle;
    friend class Polygons;
    friend class Rectangle;

public:
    int step = 4;                           // Display step
    int coord_x = 0;                        // Initial X coordinate
    int coord_y = 0;                        // Initial Y coordinate
    string shape;                           // The name of the shape

    Shape(string str)
    {
        shape = str;
        cout << "Enter the number of the shapes = ";
        cin >> amount;
    }

    vector<pair<int, int>> GetCoordinates()
    {
        return coordinates;
    }
    
    ~Shape() {}

private:
    vector<pair<int, int>> coordinates;     // Coordinates of the shapes
    int amount;                             // The number of the shapes

    //! For circle / polygon
    int radius;                             // The radius of the circle / polygon
    int corners;                            // The number of corners of the polygon

    //! For rectangle
    int height;                             // Rectangle's height
    int width;                              // Rectangle's width

    //! Ìåòîä SetCoordinates çàïèñûâàåò êîîðäèíàòû ôèãóð â coordinates
    //! Method SetCoodinates records the coordinates of the shapes into vector coordinates
    void SetCoordinates(vector<pair<int, int>>& coordinates, string str)
    {
        int counter = 1;    // Counter
        
        coordinates.push_back({ coord_x, coord_y });

        //! Standard window size 800:600
        while (counter < amount)
        {
            if (str == "circle" || str == "polygon") {      // For circle / polygon
                if ((coord_x + 4 * radius + step) <= 800)
                    coord_x += (radius + radius + step);
                else {
                    coord_x = 0;
                    if (coord_y + 4 * radius + step <= 600)
                        coord_y += (radius + radius + step);
                    else
                        break;
                }
            }
            else {                                          // For rectangle
                if ((coord_x + width + width + step) <= 800)
                    coord_x += (width + step);
                else {
                    coord_x = 0;
                    if (coord_y + height + height + step <= 600)
                        coord_y += (height + step);
                    else
                        break;
                }
            }
            coordinates.push_back({ coord_x, coord_y });
            counter++;
        }
    }
};

//! Circle
class Circle : public Shape
{
public:
    Circle(int radiusIn) : Shape("circle")
    {
        radius = radiusIn;
        SetCoordinates(coordinates, shape);
    }
    
    ~Circle() {}
    
    int GetTheRadiusOfTheShape()
    {
        return radius;
    } 
};

//! Polygon
class Polygons : public Shape
{
public:
    Polygons(int cornersIn, int radiusIn) : Shape("polygon")
    {
        corners = cornersIn;
        radius = radiusIn;
        SetCoordinates(coordinates, shape);
    }

    ~Polygons() {}

    int GetTheRadiusOfTheShape()
    {
        return radius;
    }

    int GetCorners()
    {
        return corners;
    }
};

//! Rectangle / Square
class Rectangle : public Shape
{
public:
    Rectangle(int widthIn, int heightIn) : Shape("rectangle")
    {
        height = heightIn;
        width = widthIn;
        SetCoordinates(coordinates, shape);
    }

    pair<int, int> GetDimensions()
    {
        return { width, height };
    }

    ~Rectangle() {}
};

void animationSequenceCircle(sf::RenderWindow& window, sf::CircleShape& circle, int x, int y, int radius) 
{
    circle.setRadius(radius);                   // Set radius of particle[i] to r
    circle.setPosition(x, y);                   // Update position of circle in window
    circle.setFillColor(sf::Color::Blue);       // Fill color blue
    window.draw(circle);                        // Draw polygon in rendered window
    window.display();                           // Display on screeen what has been rendered to the window so far
}

void animationSequenceRectangle(sf::RenderWindow& window, sf::RectangleShape& rect, int x, int y, int width, int height) 
{    
    rect.setSize(sf::Vector2f(width, height));  // Set size of rectangle
    rect.setPosition(x, y);                     // Update position of rectangle in window
    rect.setFillColor(sf::Color::Blue);         // Fill color blue
    window.draw(rect);                          // Draw rectangle in rendered window
    window.display();                           // Display on screeen what has been rendered to the window so far
}

void animationSequencePolygon(sf::RenderWindow& window, sf::CircleShape& polygon, int x, int y, int corners, int radius) 
{
    polygon.setRadius(radius);                  // Set radius of particle[i] to r
    polygon.setPointCount(corners);             // Set the number of corners
    polygon.setPosition(x, y);                  // Update position of circle in window
    polygon.setFillColor(sf::Color::Blue);      // Fill color blue
    window.draw(polygon);                       // Draw polygon in rendered window
    window.display();                           // Display on screeen what has been rendered to the window so far
}

int main()
{   
    string str;

    cout << "--------------------------------------------------------------" << endl;
    cout << "Enter the name of the shape (circle/ rectangle/ polygon) = ";
    cin >> str;
    cout << "--------------------------------------------------------------" << endl;

    if (str == "circle")
    {
        int radius;

        cout << "Enter the radius of the circle = ";
        cin >> radius;
        if (radius <= 0) {
            cout << "It's incorrect. The radius must be greater than 0. Try again" << endl;
            return 0;
        }

        Circle cir(radius);
        vector <pair<int, int>> coord = cir.GetCoordinates();
        vector<sf::CircleShape> shapes(coord.size());

        sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

        int k = 0;
        while (window.isOpen())
        {
            if (k >= coord.size())
                k = 0;

            //! check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            //! call to function animationSequence() to simulate particles
            animationSequenceCircle(window, shapes[k], coord[k].first, coord[k].second, cir.GetTheRadiusOfTheShape());
            k++;
        }
    }
    else if (str == "polygon")
    {
        int corners, radius;

        cout << "Enter the number of angles in the polygon = ";
        cin >> corners;
        if (corners < 3) {
            cout << "It's incorrect. The value of the corners must be greater than 2";
            return 0;
        }
        cout << "Enter the radius of the polygon = ";
        cin >> radius;

        Polygons polyg(corners, radius);
        vector <pair<int, int>> coord = polyg.GetCoordinates();
        vector<sf::CircleShape> shapes(coord.size());
        
        sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

        int k = 0;
        while (window.isOpen())
        {
            if (k >= coord.size())
                k = 0;

            //! check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            //! call to function animationSequence() to simulate particles
            animationSequencePolygon(window, shapes[k], coord[k].first, coord[k].second, polyg.GetCorners(), polyg.GetTheRadiusOfTheShape());
            k++;
        }
    }
    else if (str == "rectangle")
    {
        int height, width;

        cout << "Enter the width of the rectangle = ";
        cin >> width;
        if (width <= 0) {
            cout << "It's incorrect. The width must be greater than 0. Try again" << endl;
            return 0;
        }
        cout << "--------------------------------------------------------------" << endl;
        cout << "Enter the height of the rectangle = ";
        cin >> height;
        if (height <= 0) {
            cout << "It's incorrect. The height must be greater than 0. Try again" << endl;
            return 0;
        }

        Rectangle rect(width, height);
        vector <pair<int, int>> coord = rect.GetCoordinates();
        vector<sf::RectangleShape> shapes(coord.size());
        
        sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

        int k = 0;
        while (window.isOpen())
        {
            if (k >= coord.size())
                k = 0;

            //! check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            //! call to function animationSequence() to simulate particles
            animationSequenceRectangle(window, shapes[k], coord[k].first, coord[k].second, rect.GetDimensions().first, rect.GetDimensions().second);
            k++;
        }
    }
    else {
        cout << "The name of the shape is not correct. Try again" << endl;
        return 0;
    }
    
    return 0;
}
