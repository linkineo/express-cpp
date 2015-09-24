#ifndef EXPRESS_ENUM_APPLICATION_HPP
#define EXPRESS_ENUM_APPLICATION_HPP

#include <request/request.hpp>
#include <response/response.hpp>
#include <router/common_types.hpp>

namespace express {

    typedef std::function<void(request,response)> routeHandler;
    struct handler {
        routeHandler func;
        regx_params params;
    };
    typedef std::map<http_verb,handler> actions;
    typedef std::map<routePath,actions> dispatcherMap;


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

        void connect_route(const http_verb verb,HttpServer::Response& res,std::shared_ptr<HttpServer::Request> req);
        void extract_parameters(const routePath clientPath,const routePath serverRegx,regx_params &regParamList,paramMap& pMap);
        void register_route(const http_verb verb,const routePath route,const routeHandler rHandler);

        dispatcherMap _routing;
    };

}

#endif

