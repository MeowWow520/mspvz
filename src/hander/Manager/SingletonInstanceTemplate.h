#pragma once

#ifndef SINGLETONINSTANCETEMPLATE_H
#define SINGLETONINSTANCETEMPLATE_H



template <typename T>
class SITemplate {

public:
	static T* Instance() {
		if (!_Sitemplate) _Sitemplate = new	T();
		return _Sitemplate;
	}

protected:
	SITemplate() = default;
	~SITemplate() = default;
	SITemplate(const SITemplate&) = delete;
	SITemplate& Operator=(const SITemplate&) = delete;
	
private:
	static T* _Sitemplate;
};
template <typename T>
T* SITemplate<T>::_Sitemplate = nullptr;
#endif // !SINGLETONINSTANCETEMPLATE_H