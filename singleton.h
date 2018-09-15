#ifndef SINGLETON_H
#define SINGLETON_H

/** simple singleton class. Not thread safe!
   */
template <typename T>
class Singleton
{
  public:
    static T &getInstance()
    {
        if (_instance == 0)
        {
            _instance = new T;
        }

        return *_instance;
    };

    static void destroyInstance()
    {
        if (_instance != 0)
        {
            delete _instance;
            _instance = 0;
        }
    }

  protected:
    Singleton(){};
    virtual ~Singleton(){};

  private:
    Singleton(const Singleton &){};
    static T *_instance;
};

template <typename T>
T *Singleton<T>::_instance = 0;

#endif // SINGLETON_H
