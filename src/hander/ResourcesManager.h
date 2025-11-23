#pragma once
#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include "SingletonInstanceTemplate.h"

class ResourcesManager : public Manager<ResourcesManager> {
    friend class Manager<ResourcesManager>;

public:

protected:
    ResourcesManager() = default;
    ~ResourcesManager() = default;
private:

};

#endif // RESOURCESMANAGER_H