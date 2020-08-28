#include "pch.h"
#include "ResourceManager.h"

bool nc::ResourceManager::Startup()
{
    return true;
}

void nc::ResourceManager::Shutdown()
{

}

void nc::ResourceManager::Update()
{

}

void nc::ResourceManager::RemoveAll()
{
    for (auto resource : m_resources)
    {
        resource.second->Destroy();
        delete resource.second;
    }
    m_resources.clear();

}
