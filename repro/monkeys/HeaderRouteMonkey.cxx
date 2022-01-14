#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "resip/stack/SipMessage.hxx"
#include "resip/stack/Helper.hxx"
#include "repro/Proxy.hxx"
#include "repro/monkeys/HeaderRouteMonkey.hxx"
#include "repro/RequestContext.hxx"
#include "repro/QValueTarget.hxx"

#include "rutil/Logger.hxx"

#define RESIPROCATE_SUBSYSTEM resip::Subsystem::REPRO

using namespace resip;
using namespace repro;
using namespace std;

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
    msg.parseAllHeaders();
    WarningLog(<< "HELL 1: ");
    auto hdrs = msg.header(h_XZaleosTargets);

    for (const auto &hdr : hdrs)
    {
        InfoLog(<< "Header values: " << hdr.uri());
    }
    WarningLog(<< "HELL 2: ");

    // Uri ruri(msg.header(h_RequestLine).uri());
    // Data method(getMethodName(msg.header(h_RequestLine).method()));
    // Data event;
    // if (msg.exists(h_Event) && msg.header(h_Event).isWellFormed())
    // {
    //     event = msg.header(h_Event).value();
    // }

    // RouteStore::UriList targets(mRouteStore.process(ruri,
    //                                                 method,
    //                                                 event));
    // bool requireAuth = false;
    // bool externalTarget = false;
    // if (!context.getKeyValueStore().getBoolValue(IsTrustedNode::mFromTrustedNodeKey) &&
    //     msg.method() != ACK && // Don't challenge ACK and BYE requests
    //     msg.method() != BYE)
    // {
    //     requireAuth = !mNoChallenge;
    //     for (RouteStore::UriList::const_iterator i = targets.begin();
    //          i != targets.end(); i++)
    //     {
    //         const Data &targetDomain = i->host();
    //         if (!proxy.isMyDomain(targetDomain))
    //         {
    //             DebugLog(<< "target domain " << targetDomain << " is not local");
    //             externalTarget = true;
    //             requireAuth |= !mNoChallenge;
    //         }
    //     }
    // }

    // // Allow third-parties verified by their domain certificate, just as long
    // // as they don't try to use us as a relay to external targets
    // // not in our local domain list
    // if (context.getKeyValueStore().getBoolValue(CertificateAuthenticator::mCertificateVerifiedKey) && !externalTarget && requireAuth)
    // {
    //     DebugLog(<< "overriding requireAuth because certificate validation succeeded and no targets are external");
    //     requireAuth = false;
    // }

    // if (requireAuth && context.getDigestIdentity().empty())
    // {
    //     // !rwm! TODO do we need anything more sophisticated to figure out the realm?
    //     Data realm = msg.header(h_RequestLine).uri().host();

    //     challengeRequest(context, realm);
    //     return Processor::SkipAllChains;
    // }
    // else
    // {
    //     TargetPtrList parallelBatch;
    //     for (RouteStore::UriList::const_iterator i = targets.begin();
    //          i != targets.end(); i++)
    //     {
    //         //Targets are only added after authentication
    //         InfoLog(<< "Adding target " << *i);

    //         if (mParallelForkHeaderRouteMonkeys)
    //         {
    //             Target *target = new Target(*i);
    //             parallelBatch.push_back(target);
    //         }
    //         else
    //         {
    //             // Add Simple Target
    //             context.getResponseContext().addTarget(NameAddr(*i));
    //         }
    //     }
    //     if (parallelBatch.size() > 0)
    //     {
    //         context.getResponseContext().addTargetBatch(parallelBatch, false /* highPriority */);
    //     }

    //     if (!targets.empty() && !mContinueProcessingAfterRoutesFound)
    //     {
    //         return Processor::SkipThisChain;
    //     }
    // }

    return Processor::Continue;
}
