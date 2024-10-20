#pragma once

#include <imgui.h>
#include <presenter/ReactiveProperty.h>
#include <view/IUIControl.h>

namespace Forged::Presenter
{

template<typename T>
class BindingContext
{
public:
    BindingContext(ReactiveProperty<T>& property) : mProperty(property) {}
    virtual ~BindingContext() noexcept = default;

    virtual void bind() = 0;
    virtual void notifyChanges() = 0;
    virtual void unbind() { mSubscription.unsubscribe(); }
    bool isBound() { return mSubscription.issubscribe(); }
    ReactiveProperty<T>& getProperty() { return mProperty; }

protected:
    ReactiveProperty<T>& mProperty;
    ReactiveProperty<T>::Subscription mSubscription;
};

class StringBinding : public BindingContext<std::string>
{
public:
    StringBinding(ReactiveProperty<std::string>& property)
    : BindingContext(property) 
    , mBuffer(256, 0)
    {}

    void bind() override
    {
        mProperty.bind([&](const std::string &value) { mBuffer = value; });
        
        // TODO handle better setting the default value
        mBuffer = mProperty.getValue();
    }

    void notifyChanges() override
    {
        mProperty.setValue(std::string(mBuffer));
    }

    char* getBuffer() { return mBuffer.data(); }
    int getBufferCapacity() const { return mBuffer.capacity(); }

private:
    std::basic_string<char> mBuffer;
};

}
