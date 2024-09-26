#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "resip/stack/SipMessage.hxx"
#include "resip/stack/Helper.hxx"
#include "resip/stack/ExtensionHeader.hxx"
#include "repro/Proxy.hxx"
#include "repro/monkeys/HeaderRouteMonkey.hxx"
#include "repro/RequestContext.hxx"
#include "repro/QValueTarget.hxx"

#include "rutil/Logger.hxx"

#define RESIPROCATE_SUBSYSTEM resip::Subsystem::REPRO

using namespace resip;
using namespace repro;
using namespace std;

static const resip::ExtensionHeader h_XZaleosTargets("X-Zaleos-Target");

HeaderRouteMonkey::HeaderRouteMonkey(ProxyConfig &config) : Processor("HeaderRouteMonkey")
{
}

HeaderRouteMonkey::~HeaderRouteMonkey()
{
}

Processor::processor_action_t
HeaderRouteMonkey::process(RequestContext &context)
{
    DebugLog(<< "Monkey handling request: " << *this
             << "; reqcontext = " << context);
    Proxy &proxy = context.getProxy();

    SipMessage &msg = context.getOriginalRequest();

    if (msg.exists(h_XZaleosTargets))
    {
        resip::SipMessageOptions opts;
        opts.mTxOptions.mTimerB = 4000; // 4sec
        opts.mTxOptions.mTimerC = 8000; // 8sec
        const StringCategories &targetHeaders = msg.header(h_XZaleosTargets);
        for (StringCategories::const_iterator it = targetHeaders.begin(); it != targetHeaders.end(); it++)
        {
            auto targetHdrValue = it->value();
            InfoLog(<< "Header value: " << targetHdrValue);
            // Add Simple Target
            std::unique_ptr<Target> target(new Target(NameAddr(Uri(targetHdrValue.data())), opts));
            context.getResponseContext().addTarget(std::move(target));
        }
    }
    else
    {
        WarningLog(<< "Can't find X-Zaleos-Target headers");
    }

    // return Processor::SkipThisChain;
    return Processor::Continue;
}
