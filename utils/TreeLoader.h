#pragma once
#include <stdlib.h>
#include <time.h>  
#include <string>

// TODO: map structure representing all the possibilities

class Node
{
public:
	Node(std::string path, std::string assetsPath, std::string texturePath, int triggerX = -1, int triggerY = -1, Node* rightNode = nullptr, Node* leftNode = nullptr, Node* parentNode = nullptr)
		: _path(path), _assetsPath(assetsPath), _texturePath(texturePath), _triggerX(triggerX), _triggerY(triggerY),
		_rightNode(rightNode), _leftNode(leftNode), _parentNode(parentNode)
	{}
	std::string _path;
	std::string _assetsPath;
	std::string _texturePath;
	// TODO: use vector class
	int _triggerX;
	int _triggerY;
	Node* _rightNode;
	Node* _leftNode;
	Node* _parentNode;
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
		_root = node;
		Node* currentNode = _root;

		while (currentNode->_rightNode != nullptr)
		{
			// TODO: randomize left or right
			Node* prevNode = currentNode;
			currentNode = currentNode->_rightNode;
			currentNode->_parentNode = prevNode;
		}

		currentNode->_rightNode = node;
	}

	void generateNodes() {
		// TODO: add option to trigger randomization via keyboard input (debug mode)
		int random = 5;
		for (int i = 0; i < random; i++)
		{
			// bound tile randomization to the edges of the map
			int randX, randY;
			std::string directions[4] = { "top", "right", "bottom", "left" };
			int randomDirection = (rand() % 4 + 1) - 1;

			if (directions[randomDirection] == "top")
			{
				randY = 0;
				randX = (rand() % 30 + 1) - 1;
			}
			else if (directions[randomDirection] == "right")
			{
				randY = (rand() % 17 + 1) - 1;
				randX = 29;
			}
			else if (directions[randomDirection] == "bottom")
			{
				randY = 16;
				randX = (rand() % 30 + 1) - 1;
			}
			else if (directions[randomDirection] == "left")
			{
				randY = (rand() % 17 + 1) - 1;
				randX = 0;
			}

			Node* node = new Node("assets/levels/level-1.json", _maps[0], _texturePath, randX, randY);
			addNode(node);
		}
	}
	std::string _texturePath = "assets/maps/office-atlas.png";
	std::string _maps[5] = {
		"assets/maps/office-1.json",
		"assets/maps/office-2.json",
	};
	Node* _root = nullptr;
};