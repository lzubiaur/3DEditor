#pragma once

#include <services/IService.h>
#include <boost/signals2.hpp>
#include <gsl/assert>

namespace Engine
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
{};

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
    // std::shared_ptr<Signal<Signature>> getSignal(const std::string& signalId)
    auto getSignal(const std::string& signalId)
    {
        Expects(mRegistery.find(signalId) != mRegistery.end());

        return std::static_pointer_cast<Signal<Signature>>(mRegistery.at(signalId));
    }

    void onShutdown()
    {
        // TODO disconnect all signals
    }

private:
    std::unordered_map<std::string, std::shared_ptr<ISignal>> mRegistery;
};

}