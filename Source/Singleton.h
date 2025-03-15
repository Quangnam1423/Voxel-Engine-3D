#pragma once

template<typename T>
class Singleton
{
private:
    static T* m_instance;
public:
    // delete constructor
    Singleton(const Singleton&) = delete;

    // delete operator = to prevent copying instance
    Singleton& operator = (const Singleton&) = delete;

    // delete constructor;
    static T* getInstance() {
        if (m_instance == nullptr)
        {
            m_instance = new T();
        }
        return m_instance;
    }
protected:
    //constructor
    Singleton() = default;
    //destructor
    virtual ~Singleton() = default;

};

template<typename T>
T* Singleton<T>::m_instance = nullptr;