#include <SFML/Graphics.hpp>
#include <iostream>
#include "headerfloor.h"
using namespace std;

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Floor Plan");  //sfml window
//    sf::Font font;
//    //font.loadFromFile("SynthaNovaBlack-JRZv7.ttf");
//    if (!font.loadFromFile("f.ttf"))
//    {
//        cout<<"font not loaded";
//    }
//    sf::Text text;
//    //text.setFont(font);
//    text.setCharacterSize(24);
//    text.setFillColor(sf::Color::Red);
//    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
//    text.setString("Hello world");
    //text.setPosition(10.f, 50.f);

    vector<sf::RectangleShape> shapes;//(sf::Vector2f(200.0f,100.0f));
    ifstream srcfile;
    srcfile.open("netlist.txt");
    vector <block> blocks;
    int area=0;

    readBlocks(blocks,srcfile);                //reading from source file
    //srcfile.close();
    vector <vector <node>> grid;              //matrix grid to store full points
    vector <node> tempVec;grid.push_back(tempVec);
    //vector <point> testPoints;
    vector <pair<int,int>> testPoints;     //points to be tested as potential placement points
    testPoints.push_back(make_pair(0,0));
    //cout<<points[0].first<<" "<<points[0].first;

    sf::Clock Clock;
    Clock.restart();
    int i=0;
    int previ=1;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased){
                if (event.key.code == sf::Keyboard::Space){
                    i++;
                }
            }
        }
        window.clear();
//        window.draw(text);
//             drawing grid empty and full cells
        for (int k=0;k<grid.size();k++){
            for (int j=0;j<grid[k].size();j++){
                if(grid[k][j].full==1){
                    window.draw(gateShape(j,k,9,1,1));
                }else if(grid[k][j].full==0){
                    window.draw(gateShape(j,k,10,1,1));
                }
            }
        }
        // drawing old shapes
        for (int j=0;j<shapes.size();j++){
            window.draw(shapes[j]);
        }
        if (i<blocks.size()&& i!=previ){
            area+=blocks[i].l*blocks[i].w;
            int fixPointID=0;
            bool flip;

            findPoint(blocks[i],grid,testPoints,fixPointID,flip);  // finds best point to place the block
            //,,,second,blocks[i].w
            if(flip){
                int temp=blocks[i].l;blocks[i].l=blocks[i].w;blocks[i].w=temp;  //flips dimensions if block needs to be flipped
            }
            shapes.push_back(gateShape(testPoints[fixPointID].first,testPoints[fixPointID].second,blocks[i].typeID,blocks[i].l,blocks[i].w));

            //cout<<"done";
            updateGrid(blocks[i],grid,testPoints[fixPointID]);     //updates the grid to mark full points and reevaluate size
            updatePoints(blocks[i],testPoints,fixPointID);         //adds potential points and removes current fix point
            //shapes.push_back(gateShape(0,0,9,grid[0].size(),grid.size()));
            cout<<"aspect Ratio:"<<float(min(grid.size(),grid[0].size()))/float(max(grid.size(),grid[0].size()))<<endl;
            cout<<"dead space:"<<(1-float(area)/float(grid.size()*grid[0].size()))*100<<"%"<<endl;
            cout<<"Press space bar!";
        }

        window.display();

            previ=i;
            //i=int(Clock.getElapsedTime().asSeconds()/10);


    }

//    //shapes = gateShape(0,5,1,3,1);
//    sf::Clock Clock;
//    Clock.restart();
//    while (window.isOpen())
//    {
//
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//
//        int stop = min(int(Clock.getElapsedTime().asSeconds()*2),int(shapes.size()));
//        for (int i=0;i<stop;i++){
//            window.draw(shapes[i]);
//            if (i%2==1){
//                for (int j=0;j<i;j+=2){
//                    window.draw(shapes[j]);
//                }
//            }
//        }
////        for (int i=0;i<shapes.size();i++){
////            window.draw(shapes[i]);
////        }
//        //window.draw(shapes[i]);
//        window.display();
//    }
    return 0;
}


//#include "headerfloor.h"
//int main()
//{
////    float x = 100;
////    float y = 100; //gate position
////    int gate = 1;  //Gate type
////    float length = 2;
////    float width = 1;
//    sf::RenderWindow window(sf::VideoMode(600, 600), "Floor Plan");
//    sf::RectangleShape shapes;//(sf::Vector2f(200.0f,100.0f));
//
//    shapes = gateShape(0,5,1,3,1);
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shapes);
//        window.display();
//    }
//
//    return 0;
//}
