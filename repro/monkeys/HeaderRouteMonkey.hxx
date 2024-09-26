#if !defined(RESIP_HEADERROUTEMONKEY_HXX)
#define RESIP_HEADERROUTEMONKEY_HXX

#include "repro/Processor.hxx"
#include "repro/ProxyConfig.hxx"

namespace repro
{
    class HeaderRouteMonkey : public Processor
    {
    public:
        HeaderRouteMonkey(ProxyConfig &config);
        virtual ~HeaderRouteMonkey();

        virtual processor_action_t process(RequestContext &);
    };
}
#endif