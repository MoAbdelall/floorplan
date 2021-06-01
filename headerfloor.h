#ifndef HEADERFLOOR_H_INCLUDED
#define HEADERFLOOR_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
//struct point {
//    int x,y;
//};
struct node{
    bool full=0;
};
struct block {
    string type;
    int typeID;
    string name;
    int ID;
    int n;
    //bool fixed=0;
    int l,w;
    int area;
};
//gate_type:
    //NOT     AND      OR      XOR      FF     NAND        NOR     XNOR
    // 1       2        3       4        5       6          7        8
    //green    blue    red    White   yellow   Magenta     Cyan    Orange
sf::RectangleShape gateShape(float x, float y, int gate, float length, float width )  //draws shapes with colors
{
    float ps = 20; //Number of pixels
    sf::RectangleShape shape(sf::Vector2f(length * ps,width * ps));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(sf::Vector2f(x*ps,y*ps));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1);
    switch (gate)
    {
     case 1:
        shape.setFillColor(sf::Color(0, 184, 148));
     break;
     case 2:
        shape.setFillColor(sf::Color(9, 132, 227));
     break;
     case 3:
        shape.setFillColor(sf::Color(214, 48, 49));
     break;
     case 4:
        shape.setFillColor(sf::Color::White);
     break;
     case 5:
        shape.setFillColor(sf::Color(241, 196, 15));
     break;
     case 6:
        shape.setFillColor(sf::Color::Magenta);
     break;
     case 7:
        shape.setFillColor(sf::Color(116, 185, 255));
     break;
     case 8:
        shape.setFillColor(sf::Color(255,140,0));
     break;
     case 9:
        shape.setFillColor(sf::Color(223, 230, 233));
     break;
     case 10:
        shape.setFillColor(sf::Color(223, 230, 233,50));
     break;
     default:
         shape.setFillColor(sf::Color::Green);
    }
return shape;
}
// Determines block dimensions
findBlockDims(block &tempBlock){
    if (tempBlock.type=="Inv"){
        tempBlock.typeID=1;
        tempBlock.l=2;
        tempBlock.w=1;
    }else if(tempBlock.type=="And"){
        tempBlock.typeID=2;
        tempBlock.l=tempBlock.n+1;
        tempBlock.w=tempBlock.n+1;
    }else if(tempBlock.type=="Or"){
        tempBlock.typeID=3;
        tempBlock.l=tempBlock.n+1;
        tempBlock.w=tempBlock.n+1;
    }else if(tempBlock.type=="Xor"){
        tempBlock.typeID=4;
        tempBlock.l=2*tempBlock.n;
        tempBlock.w=tempBlock.n+2;
    }else if(tempBlock.type=="Flipflop"){
        tempBlock.typeID=5;
        tempBlock.l=8;
        tempBlock.w=1;
    }else if(tempBlock.type=="Nand"){
        tempBlock.typeID=6;
        tempBlock.l=tempBlock.n;
        tempBlock.w=tempBlock.n;
    }else if(tempBlock.type=="Nor"){
        tempBlock.typeID=7;
        tempBlock.l=tempBlock.n;
        tempBlock.w=tempBlock.n;
    }else if(tempBlock.type=="Xnor"){
        tempBlock.typeID=8;
        tempBlock.l=2*tempBlock.n;
        tempBlock.w=tempBlock.n;
    }else{
        tempBlock.typeID=9;
        tempBlock.l=1;
        tempBlock.w=1;
    }
}
//reads source file
void readBlocks(vector<block> &blocks,ifstream &srcfile){
    string line;
    getline(srcfile,line);
    int i=0;
    while (srcfile){
        //cout<<i;
        block tempBlock;
        tempBlock.type=line.substr(0,line.find(" "));

        line.erase(0,line.find(" ")+1);
        tempBlock.name=line.substr(0,line.find(" "));
        line.erase(0,line.find(" ")+2);
        cout<<tempBlock.type<<" "<<tempBlock.typeID<<" "<<tempBlock.name;
        ////cout<<line.find(",");
        ////cout<<line.find(":");
        //if one parameter
//        if(line.find(",")==string::npos){
//            //cout<<line.substr(line.find(" ")+1,line.find(")")-1-line.find(" "))<<endl;
//            tempBlock.outnet.push_back(line.substr(line.find(" ")+1,line.find(")")-1-line.find(" ")));
//            ////cout<<tempBlock.outnet[0];
//        }else{
            //line.erase(0,line.find(" ")+1);
            ////cout<<"\n"<<line<<endl;
            string blockType=line.substr(0,3);
            //cout<<blockType<<endl;
            int n=0;
            while (blockType.compare("in ")==0 || blockType.compare("clk")==0){
                //tempBlock.innet.push_back(line.substr(line.find(" ")+1,line.find(",")-1-line.find(" ")));
                n++;
                //cout<<line.substr(line.find(" ")+1,line.find(",")-1-line.find(" "))<<" ";
                line.erase(0,line.find(",")+2);
                //cout<<line<<endl;
                blockType=line.substr(0,3);
                //cout<<blockType;
            }
            tempBlock.n=n;

            //tempBlock.outnet.push_back(line.substr(line.find(" ")+1,line.find(")")-1-line.find(" ")));
            //cout<<line.substr(line.find(" ")+1,line.find(")")-1-line.find(" "))<<endl;

//        }
        tempBlock.ID=i;
        cout<<"..."<<tempBlock.n<<" "<<tempBlock.ID<<endl;
        //tempBlock.fixed=0;
        findBlockDims(tempBlock);
        blocks.push_back(tempBlock);
        getline(srcfile,line);
        i++;
    }
//    return 0;
}
//calculates area of grid after adding the block in the fix point
int calcArea(block theBlock,vector <vector <node>> grid,pair<int,int> testPoint,bool flip){
    if (flip==0){
            //cout<<grid.size()<<" "<<testPoint.first<<" "<<theBlock.l<<" "<<grid[0].size()<<" "<<testPoint.second<<" "<<theBlock.w<<endl;
            //cout<<max(int(grid.size()),testPoint.first+theBlock.l)*max(int(grid[0].size()),testPoint.second+theBlock.w);
        return max(int(grid[0].size()),testPoint.first+theBlock.l)*max(int(grid.size()),testPoint.second+theBlock.w);
    }else{
        return max(int(grid[0].size()),testPoint.first+theBlock.w)*max(int(grid.size()),testPoint.second+theBlock.l);
    }

}
// tests for conflicts with other blocks if block is added in the fix point
bool noConflict(block theBlock,vector <vector <node>> grid,pair<int,int> testPoint,bool flip){
    bool flag=1;
    if (flip==0){
        for (int i=testPoint.first;i<min(int(grid[0].size()),testPoint.first+theBlock.l);i++){
            for (int j=testPoint.second;j<min(int(grid.size()),testPoint.second+theBlock.w);j++){
                if(testPoint.first>0){
                    cout<<grid[j][i].full<<" ";
                }
                if (grid[j][i].full){
                    flag=0;
                }
            }
        }
    }else{
        for (int i=testPoint.first;i<min(int(grid[0].size()),testPoint.first+theBlock.w);i++){
            for (int j=testPoint.second;j<min(int(grid.size()),testPoint.second+theBlock.l);j++){
                if (grid[j][i].full){
                    flag=0;
                }
            }
        }
    }

    return flag;
}
//finds the best placement point
void findPoint(block theBlock,vector <vector <node>> grid,vector <pair<int,int>> &testPoints,int &fixPointID,bool &flip){
    int minArea;
    bool First=1;
    flip=0;
    cout<<"============================"<<endl;
    cout<<"testing "<<theBlock.name<<" "<<theBlock.l<<" by "<<theBlock.w<<" :"<<endl;
    if (grid[0].size()*4>grid.size()*10 && grid.size()*grid[0].size()>10){
        testPoints.push_back(make_pair(0,grid.size()));
        fixPointID=testPoints.size()-1;
    }else if(grid.size()*4>grid[0].size()*10 && grid.size()*grid[0].size()>10){
        testPoints.push_back(make_pair(0,grid[0].size()));
        fixPointID=testPoints.size()-1;
    }else{
    for (int i=0;i<testPoints.size();i++){
            cout<<"at "<<testPoints[i].first<<","<<testPoints[i].second<<" : "<<endl;
//        if (grid[0].size()*4>grid.size()*10 && grid.size()*grid[0].size()>10){
//        //if (grid[0].size()>grid.size()){
//            if(First){
//                 fixPointID=i;
//            }else{
//                if(testPoints[i].second>testPoints[fixPointID].second||(testPoints[i].second==testPoints[fixPointID].second&& testPoints[i].first<testPoints[fixPointID].first)){
//                    fixPointID=i;
//                }
//            }
//        }else if(grid[0].size()*3<grid.size()*2){
//            if(First){
//                 fixPointID=i;
//            }else{
//                if(testPoints[i].first>testPoints[fixPointID].first||(testPoints[i].first==testPoints[fixPointID].first&& testPoints[i].second<testPoints[fixPointID].second)){
//                    fixPointID=i;
//                }
//            }
//        }
        //else
        if (noConflict(theBlock,grid,testPoints[i],0)){
            cout<<"No Conflict ";
            if(First){
                //cout<<"done "<<i;
                minArea=calcArea(theBlock,grid,testPoints[i],0);
                cout<<"First Area="<<minArea<<" Taken"<<endl;
                fixPointID=i;
                flip=0;
                First=0;
                //cout<<"done "<<i;
            }else{
                cout<<" Area="<<calcArea(theBlock,grid,testPoints[i],0);
                if(calcArea(theBlock,grid,testPoints[i],0)<=minArea){
                    cout<<" Taken"<<endl;
                    minArea=calcArea(theBlock,grid,testPoints[i],0);
                    fixPointID=i;
                    flip=0;
                }else{
                    cout<<" Not Taken"<<endl;
                }
            }
        }else{
            cout<<" conflicted"<<endl;
        }
        if(theBlock.l!=theBlock.w){
            cout<<" flipped "<<endl;
            if (noConflict(theBlock,grid,testPoints[i],1)){
                cout<<" No Conflict ";
                if(First){
                    cout<<" First Area="<<minArea<<" Taken"<<endl;
                    minArea=calcArea(theBlock,grid,testPoints[i],1);
                    fixPointID=i;
                    flip=1;
                    First=0;
                }else{
                    cout<<" Area="<<calcArea(theBlock,grid,testPoints[i],1);
                    if(calcArea(theBlock,grid,testPoints[i],1)<minArea){
                        cout<<" Taken"<<endl;
                        minArea=calcArea(theBlock,grid,testPoints[i],1);
                        fixPointID=i;
                        flip=1;
                    }else{
                        cout<<" Not Taken"<<endl;
                    }
                }
            }else{
                cout<<" conflicted"<<endl;
            }
        }else{
            cout<<" Not flipped"<<endl;
        }
    }
    }
//    if(minArea>grid.size()*grid[0].size()){
//            for (int i=0;i<testPoints.size();i++){
//                First=1;
//                    if (grid[0].size()>grid.size()){
//                        if(First){
//                            fixPointID=i;
//                        }else{
//                            if(testPoints[i].second>testPoints[fixPointID].second||(testPoints[i].second==testPoints[fixPointID].second&& testPoints[i].first<testPoints[fixPointID].first)){
//                                fixPointID=i;
//                            }
//                        }
//                    }else{
//                        if(First){
//                            fixPointID=i;
//                        }else{
//                            if(testPoints[i].first>testPoints[fixPointID].first||(testPoints[i].first==testPoints[fixPointID].first&& testPoints[i].second<testPoints[fixPointID].second)){
//                                fixPointID=i;
//                            }
//                        }
//                    }
//                }
//    }

}
//adds potential points and removes current fix point
void updatePoints(block theBlock,vector <pair<int,int>> &testPoints,int fixPointID){
    testPoints.push_back(make_pair(testPoints[fixPointID].first+theBlock.l,testPoints[fixPointID].second));
    testPoints.push_back(make_pair(testPoints[fixPointID].first,testPoints[fixPointID].second+theBlock.w));
    testPoints.erase(testPoints.begin()+fixPointID);

}
//updates the grid to mark full points and reevaluate size
void updateGrid(block theBlock,vector <vector <node>> &grid,pair<int,int> fixPoint){
    int x=max(int(grid[0].size()),fixPoint.first+theBlock.l);
    int y=max(int(grid.size()),fixPoint.second+theBlock.w);
    cout<<"x="<<x<<" y="<<y<<endl;
    node tempNode;
    tempNode.full=0;
    vector <node> tempVecNode;
    for(int j=0;j<grid.size();j++){
        for (int i=grid[j].size();i<x;i++){
            cout<<"added node at: "<<i<<","<<j<<endl;
            grid[j].push_back(tempNode);
        }
    }
    for (int j=grid.size();j<y;j++){
        for (int i=0;i<x;i++){
            tempVecNode.push_back(tempNode);
        }
        cout<<"added row of size: "<<tempVecNode.size()<<", at"<<j<<endl;
        grid.push_back(tempVecNode);
        tempVecNode.clear();
    }
    for (int i=fixPoint.first;i<fixPoint.first+theBlock.l;i++){
        for(int j=fixPoint.second;j<fixPoint.second+theBlock.w;j++){
                //cout<<"got here";
            //cout<<"i"<<i<<"j"<<j<<endl;
            grid[j][i].full=1;
                //cout<<"got here";
        }
    }
}


#endif // HEADERFLOOR_H_INCLUDED
