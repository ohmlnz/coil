#include "TreeLoader.h"

TreeLoader::TreeLoader() {
	srand(time(NULL));
	generateNodes();
}

Node* TreeLoader::getRootNode() {
	return _root;
}

void TreeLoader::deleteNode(Node* node) {
	// TODO: link parent to siblings
	delete node;
}

void TreeLoader::addNode(Node* node) {
	if (node->_id == 0)
	{
		_root = node;
		return;
	}

	Node* currentNode = _root;

	while (true)
	{
		if (rand() % 2 == 0)
		{
			if (currentNode->_rightNode != nullptr)
			{
				currentNode = currentNode->_rightNode;
			}
			else
			{
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

void TreeLoader::printBT(const std::string& prefix, const Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "L__" : "R__");

		std::cout << node->_id << std::endl;

		printBT(prefix + (isLeft ? "|   " : "    "), node->_leftNode, true);
		printBT(prefix + (isLeft ? "|   " : "    "), node->_rightNode, false);
	}
}

void TreeLoader::printBT(const Node* node)
{
	printBT("", node, false);
}

void TreeLoader::appendMapData(Node* node) {
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

std::string TreeLoader::findMap(Node* node) {
	bool hasParentNode = node->_parentNode != nullptr;
	int nbOfNeededDoors = int(hasParentNode) + int(node->_leftNode != nullptr) + int(node->_rightNode != nullptr);
	std::vector<Node> randomNodes;

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
			if (!hasParentNode)
			{
				Node newNode;
				newNode._mapPath = map;
				for (int i = 0; i < nbOfAvailableDoors; i++)
				{
					newNode._doorsLocation.push_back(getDoorIndex(currentDoors[i]));
				}
				randomNodes.push_back(newNode);
			}
			else
			{
				int parentDoor = getParentDoor(node);
				int opposedToParentDoor = getOppositeDoor(parentDoor);

				for (int i = 0; i < nbOfAvailableDoors; i++)
				{
					if (getDoorIndex(currentDoors[i]) == opposedToParentDoor)
					{
						Node newNode;
						newNode._mapPath = map;
						newNode._opposedToParentDoor = opposedToParentDoor;
						for (int i = 0; i < nbOfAvailableDoors; i++)
						{
							newNode._doorsLocation.push_back(getDoorIndex(currentDoors[i]));
						}
						randomNodes.push_back(newNode);
						break;
					}
				}
			}
		}

	}
	Node selectedNode = randomNodes[rand() % randomNodes.size()];
	node->_doorsLocation = selectedNode._doorsLocation;
	node->_opposedToParentDoor = selectedNode._opposedToParentDoor;
	return selectedNode._mapPath;
}

int TreeLoader::getOppositeDoor(int doorIndex) {
	if (doorIndex <= 1)
	{
		return doorIndex + 2;
	}
	else
	{
		return doorIndex - 2;
	}
}

int TreeLoader::getParentDoor(Node* currentNode) {
	Node* parentNode = currentNode->_parentNode;
	bool hasParentTwoSiblings = (parentNode->_leftNode != nullptr) && (parentNode->_rightNode != nullptr);
	std::vector<int> doors = parentNode->_doorsLocation;
	std::sort(doors.begin(), doors.end());

	if (parentNode->_parentNode == nullptr)
	{
		if (!hasParentTwoSiblings)
		{
			return doors[0];
		}
		else
		{
			if (parentNode->_rightNode == currentNode)
			{
				return doors[0];
			}
			else
			{
				return doors[1];
			}
		}
	}
	else
	{
		std::vector<int> filteredDoors;

		for (auto door : doors)
		{
			if (door != parentNode->_opposedToParentDoor)
			{
				filteredDoors.push_back(door);
			}
		}

		if (!hasParentTwoSiblings)
		{
			return filteredDoors[0];
		}
		else
		{
			if (parentNode->_rightNode == currentNode)
			{
				return filteredDoors[0];
			}
			else
			{
				return filteredDoors[1];
			}
		}
	}
}

int TreeLoader::getDoorIndex(std::string door) {
	if (door == "top") return 0;
	if (door == "right") return 1;
	if (door == "bottom") return 2;
	if (door == "left") return 3;
}

void TreeLoader::generateNodes() {
	// TODO: add option to trigger randomization via keyboard input (debug mode)
	int random = rand() % 11 + 10;

	for (int index = 0; index < random; index++)
	{
		Node* node = new Node(index);
		addNode(node);
	}
	printBT(_root);
	std::cout << std::endl;
	appendMapData(_root);
}