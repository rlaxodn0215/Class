#pragma once
template<typename T>
class SingletonTemplate
{
	static T* m_Instance;

public: 
	static T* GetInstance();
	void Release();
};

template<typename T>
T* SingletonTemplate<T>::m_Instance = nullptr;

template<typename T>
T* SingletonTemplate<T>::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new T;
	}

	return m_Instance;
}

template<typename T>
void SingletonTemplate<T>::Release()
{
	delete m_Instance;
	m_Instance = nullptr;
}

