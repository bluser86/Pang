#include "Include.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_objects.begin(), _objects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* obj)
{
	_objects.insert(std::pair<std::string, VisibleGameObject*>(name, obj));
}

void GameObjectManager::Remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _objects.find(name);
	if (results != _objects.end())
	{
		delete results->second;
		_objects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _objects.find(name);
	if (results == _objects.end())
	{
		return NULL;
	}
	return results->second;
}

int GameObjectManager::GetObjectCount() const
{
	return _objects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow& window)
{
	std::map<std::string, VisibleGameObject*>::const_iterator it = _objects.begin();
	while (it != _objects.end())
	{
		it->second->Draw(window);
		it++;
	}
}

void GameObjectManager::UpdateAll(sf::Time elapsed)
{
	std::map<std::string,VisibleGameObject*>::const_iterator itr = 
		_objects.begin();

	while(itr != _objects.end())
	{
		itr->second->Update(elapsed);
		itr++;
	}

}