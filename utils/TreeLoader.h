#pragma once
#include <stdlib.h>
#include <time.h>  
#include <string>
#include <iostream>
#include <queue>

class Node
{
public:
	Node(int id, int direction, Node* rightNode = nullptr, Node* leftNode = nullptr, Node* parentNode = nullptr)
		: _id(id), _direction(direction), _rightNode(rightNode), _leftNode(leftNode), _parentNode(parentNode)
	{}
	int _id;
	int _direction;
	Node* _rightNode;
	Node* _leftNode;
	Node* _parentNode;
	std::string _mapPath;
	std::vector<int> _doorsLocation;
private:

};

class TreeLoader
{
public:
	TreeLoader() {
		// initialize random seed
		srand(time(NULL));

		generateNodes();
	}

	Node* getRootNode() {
		return _root;
	}

	void searchNode(int id) {

	}
private:
	void deleteNode(Node* node) {
		delete node;
	}

	void addNode(Node* node) {
		if (node->_id == 0)
		{
			_root = node;
			return;
		}

		Node* currentNode = _root;
		bool isRightNode;

		while (true)
		{
			isRightNode = rand() % 2 == 0;
			if (isRightNode)
			{
				if (currentNode->_rightNode != nullptr)
				{
					currentNode = currentNode->_rightNode;
				}
				else {
					currentNode->_rightNode = node;
					break;
				}
			}
			else
			{
				if (currentNode->_leftNode != nullptr)
				{
					currentNode = currentNode->_leftNode;
				}
				else
				{
					currentNode->_leftNode = node;
					break;
				}
			}
		}
		node->_parentNode = currentNode;
	}

	void printBT(const std::string& prefix, const Node* node, bool isLeft)
	{
		if (node != nullptr)
		{
			std::cout << prefix;

			std::cout << (isLeft ? "|---" : "L__");

			std::cout << node->_id << std::endl;

			printBT(prefix + (isLeft ? "|   " : "    "), node->_leftNode, true);
			printBT(prefix + (isLeft ? "|   " : "    "), node->_rightNode, false);
		}
	}

	void printBT(const Node* node)
	{
		printBT("", node, false);
	}

	void appendMapData(Node* node) {
		std::queue<Node*> q;
		q.push(_root);

		while (!q.empty())
		{
			Node* temp = q.front();
			q.pop();

			temp->_mapPath = findMap(temp);

			std::cout << "Node id: " << temp->_id;
			std::cout << " was assigned the following map: " << temp->_mapPath << std::endl;

			if (temp->_leftNode != nullptr)
			{
				q.push(temp->_leftNode);
			}

			if (temp->_rightNode != nullptr)
			{
				q.push(temp->_rightNode);
			}
		}
	}

	std::string findMap(Node* node) {
		bool hasParentNode = node->_parentNode != nullptr;
		int nbOfNeededDoors = int(hasParentNode) + int(node->_leftNode != nullptr) + int(node->_rightNode != nullptr);

		for (auto map : _maps)
		{
			cute_tiled_map_t* loadedMap = cute_tiled_load_map_from_file(map.c_str(), NULL);
			cute_tiled_property_t* properties = loadedMap->properties;
			std::vector<std::string> currentDoors;
			const int NUMBER_OF_DOOR_PROPERTIES = 4;

			for (int i = 0; i < NUMBER_OF_DOOR_PROPERTIES; i++)
			{
				std::string name = (properties + i)->name.ptr;
				bool hasDoorProperty = name == "bottom" || name == "left" || name == "right" || name == "top";

				if (hasDoorProperty && (properties + i)->data.integer != -1)
				{
					currentDoors.push_back(name);
				}
			}

			int nbOfAvailableDoors = currentDoors.size();
			
			if (nbOfAvailableDoors == nbOfNeededDoors)
			{
				if (!hasParentNode) // root node
				{
					for (int i = 0; i < nbOfAvailableDoors; i++)
					{
						node->_doorsLocation.push_back(getDoorIndex(currentDoors[i]));
					}
					return map;
				}
				else
				{
					int parentDoor = getParentDoor(node->_parentNode->_doorsLocation);
					int opposedToParentDoor = getOpposedDoor(parentDoor);
					
					for (int i = 0; i < nbOfAvailableDoors; i++)
					{
						if (getDoorIndex(currentDoors[i]) == opposedToParentDoor)
						{
							for (int i = 0; i < nbOfAvailableDoors; i++)
							{
								node->_doorsLocation.push_back(getDoorIndex(currentDoors[i]));
							}
							return map;
						}
					}
					
				}
			}

		}

		return "no-map-found";
	}

	int getOpposedDoor(int doorIndex) {
		if (doorIndex <= 1)
		{
			return doorIndex + 2;
		}
		else
		{
			return doorIndex - 2;
		}
	}

	int getParentDoor(std::vector<int> doors) {
		int minVal = doors[0];

		for (auto door : doors)
		{
			if (door < minVal)
			{
				minVal = door;
			}
		}

		return minVal;
	}

	int getDoorIndex(std::string door) {
		if (door == "top") return 0;
		if (door == "right") return 1;
		if (door == "bottom") return 2;
		if (door == "left") return 3;
	}
	
	void generateNodes() {
		// TODO: add option to trigger randomization via keyboard input (debug mode)
		int random = 10;
		for (int index = 0; index < random; index++)
		{
			int direction = rand() % 4 + 1;
			Node* node = new Node(index, direction);
			addNode(node);
		}
		printBT(_root);
		appendMapData(_root);
	}

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