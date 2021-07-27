#pragma once
#include <stdlib.h>
#include <time.h>  
#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
#include "../libs/cute_tiled.h"

class Node
{
public:
	Node() {}
	Node(int id, Node* rightNode = nullptr, Node* leftNode = nullptr, Node* parentNode = nullptr)
		: _id(id), _rightNode(rightNode), _leftNode(leftNode), _parentNode(parentNode)
	{}
	int _id;
	Node* _rightNode;
	Node* _leftNode;
	Node* _parentNode;
	std::string _mapPath;
	std::vector<int> _doorsLocation;
	int _opposedToParentDoor = -1;
private:

};

class TreeLoader
{
public:
	TreeLoader();
	Node* getRootNode();
private:
	void deleteNode(Node* node);
	void addNode(Node* node);
	void printBT(const std::string& prefix, const Node* node, bool isLeft);
	void printBT(const Node* node);
	void appendMapData(Node* node);
	std::string findMap(Node* node);
	int getOppositeDoor(int doorIndex);
	int getParentDoor(Node* currentNode);
	int getDoorIndex(std::string door);
	void generateNodes();
	Node* _root = nullptr;
	std::string _texturePath = "assets/maps/dungeon-atlas.png";
	std::string _maps[14] = {
		"assets/maps/dungeon-1-b.json",
		"assets/maps/dungeon-1-l.json",
		"assets/maps/dungeon-1-r.json",
		"assets/maps/dungeon-1-t.json",
		"assets/maps/dungeon-2-b-l.json",
		"assets/maps/dungeon-2-l-r.json",
		"assets/maps/dungeon-2-r-b.json",
		"assets/maps/dungeon-2-t-b.json",
		"assets/maps/dungeon-2-t-l.json",
		"assets/maps/dungeon-2-t-r.json",
		"assets/maps/dungeon-3-r-b-l.json",
		"assets/maps/dungeon-3-t-b-l.json",
		"assets/maps/dungeon-3-t-l-r.json",
		"assets/maps/dungeon-3-t-r-b.json",
	};
};