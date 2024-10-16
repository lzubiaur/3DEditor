#pragma once

#include <services/IService.h>
#include <boost/signals2.hpp>
#include <gsl/assert>

namespace Engine
{

class ISignalWrapper
{
public:
    virtual ~ISignalWrapper() noexcept = default;
    virtual void disconnectAllSlots() = 0;
};

template<class T>
class SignalWrapper : public ISignalWrapper
{
public:

    void disconnectAllSlots() override
    {
        mSig.disconnect_all_slots();
    }

    boost::signals2::signal<T> mSig;
};

class Connection
{
public:
    Connection(boost::signals2::connection connection) : mConnection(connection) {}

    void disconnect()
    {
        mConnection.disconnect();
    }

private:
    boost::signals2::connection mConnection;
};

class SignalService : public IService
{
public:
    using SignalWrapperPtr = std::shared_ptr<ISignalWrapper>;

    SignalService() = default;
    ~SignalService() = default;

    template<class Signature>
    void registerSignal(const std::string& signalId)
    {
        Expects(mRegistery.find(signalId) == mRegistery.end());
        mRegistery[signalId] = std::make_shared<SignalWrapper<Signature>>();
    }

    template<class Signature>
    Connection subscribe(const std::string& signalId, const std::function<Signature>& callback)
    {
        if (mRegistery.find(signalId) == mRegistery.end())
        {
            registerSignal<Signature>(signalId);
        }

        auto wrapper = std::static_pointer_cast<SignalWrapper<Signature>>(mRegistery.at(signalId));
        
        return Connection(wrapper->mSig.connect(callback));
    }

    template <typename Signature, typename... Args>
    typename std::invoke_result<Signature, Args...>::type emit(const std::string& signalId, Args&&... args)
    {
        Expects(mRegistery.find(signalId) != mRegistery.end());
        auto wrapper = std::static_pointer_cast<SignalWrapper<Signature>>(mRegistery.at(signalId));

        return (wrapper->mSig)(std::forward<Args>(args)...);
    }

    void onShutdown() override
    {
        std::for_each(mRegistery.begin(), mRegistery.end(), [](const auto& pair)
        {
            pair.second->disconnectAllSlots();
        });
    }

private:
    std::unordered_map<std::string, SignalWrapperPtr> mRegistery;
};

}