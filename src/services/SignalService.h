#pragma once

#include <services/IService.h>
#include <boost/signals2.hpp>
#include <gsl/assert>

namespace Forged
{

class Connection
{
public: 
    Connection(boost::signals2::connection connection) : mConnection(connection) {}

    void disconnect() { mConnection.disconnect(); }
    void isConnected() { mConnection.connected(); }

private:
    boost::signals2::connection mConnection;
};

class ISignal
{
public:
    virtual ~ISignal() noexcept = default;
    virtual void disconnectAllSlots() = 0;
};

template<typename Signature>
class Signal : public ISignal
{
public:
    Connection subscribe(const std::function<Signature>& slot)
    {
        return Connection(mSig.connect(slot));
    }

    template <typename... Args>
    typename std::invoke_result<Signature, Args...>::type emit(Args&&... args)
    {
        return mSig(std::forward<Args>(args)...);
    }

    void disconnectAllSlots() override
    {
        mSig.disconnect_all_slots();   
    }
private:
    boost::signals2::signal<Signature> mSig;
};

class SignalService : public IService
{
public:

    template<typename Signature>
    auto registerSignal(const std::string& signalId)
    {
        Expects(mRegistery.find(signalId) == mRegistery.end());

        auto signal = std::make_shared<Signal<Signature>>();
        mRegistery[signalId] = signal;

        return signal;
    }

    template<typename Signature>
    auto getSignal(const std::string& signalId)
    {
        Expects(mRegistery.find(signalId) != mRegistery.end());

        return std::static_pointer_cast<Signal<Signature>>(mRegistery.at(signalId));
    }

    void onShutdown()
    {
        std::for_each(mRegistery.begin(), mRegistery.end(), [](const auto& pair)
        {
            pair.second->disconnectAllSlots(); 
        });
    }

private:
    std::unordered_map<std::string, std::shared_ptr<ISignal>> mRegistery;
};

}