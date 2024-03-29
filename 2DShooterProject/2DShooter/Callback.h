#ifndef __Callback__
#define __Callback__

class Callback
{
public:
    virtual ~Callback() {}

	virtual void call() = 0;
};

class StaticCallback : public Callback
{
public:

    StaticCallback(void (*func)()) : m_func(func)
    {
    }

    virtual void call()
    {
        m_func();
    }

private:

    void (*m_func)();
};

#endif /* defined ( __Callback__ ) */
