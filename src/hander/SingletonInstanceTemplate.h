#pragma once
#ifndef SINGLETONINSTANCEEMPLATE_H
#define SINGLETONINSTANCEEMPLATE_H



template <typename T>
class Manager {
public:
	static T* Instance() {
		if (!manager) manager = new	T();
		return manager;
	}
protected:
	Manager() = default;
	~Manager() = default;
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
private:
	static T* manager;
};
template <typename T>
T* Manager<T>::manager = nullptr;
#endif // !SINGLETONINSTANCEEMPLATE_H