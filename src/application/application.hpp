#ifndef EXPRESS_ENUM_APPLICATION_HPP
#define EXPRESS_ENUM_APPLICATION_HPP

#include <request/request.hpp>
#include <response/response.hpp>
#include <router/common_types.hpp>

namespace express {

    typedef std::function<void(request,response)> routeHandler;

    struct routeHandle {

        routeHandler rH;
        http_verb verb;

    };

    class application
    {
    public:

        application();

        void del(const routePath route,const routeHandler rHandler);
        void get(const routePath route,const routeHandler rHandler);
        void post(const routePath route,const routeHandler rHandler);
        void put(const routePath route,const routeHandler rHandler);

        void listen(int port);

    private:

        std::map<routePath,routeHandle> routing;
    };

}

#endif

