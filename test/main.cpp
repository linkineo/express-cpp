#include <iostream>
#include <application/application.hpp>
#include <client_http.hpp>

typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;

int main(int argc, char ** argv)
{
	express::application app;

    app.get("/hello",[](express::request req, express::response res) {
        res.append("X-Hello","World");
        res.send("World !");
    });

    app.get("/hello/:world",[](express::request req,express::response res) {
        std::cout << "HEADER IN USER AGENT=" << req.headers["User-Agent"] << std::endl;
        if(req.is("HTML"))
        {
            std::cout << "Accept content html"<< std::endl;
        }
        res.send("World="+ req.params["world"] + "-- query [param1]=" + req.query["param1"] + " [param2]=" + req.query["param2"]);
    });

    app.get("/hello/:id_var/age/:age",[](express::request req, express::response res) {
        res.send("Hello " + req.params["id_var"] + " ! You are " + req.params["age"] + " years old !");
    });

    app.post("/my/lamp",[](express::request req, express::response res) {
        res.send("GOT IT POSTED ! - GOT:" + req.body.string());
    });

    app.static_("/Users/linkineo/Devl/express-cpp/build");
    app.default_("index.html");

    app.listen(8010);

  return 0;
}
