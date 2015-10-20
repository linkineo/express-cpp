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
        res.send("World="+ req.params["world"] + "-- query [param1]=" + req.query["param1"] + " [param2]=" + req.query["param2"]);
    });

    app.get("/hello/:id/age/:age",[](express::request req, express::response res) {
        res.send("Hello " + req.params["id"] + " ! You are " + req.params["age"] + " years old !");
    });

    app.post("/dali/lamp",[](express::request req, express::response res) {
        res.send("GOT IT POSTED ! - GOT:" + req.body.string());
    });

    app.static_("/home/linkineo/Devl/express-cpp/build");

    app.listen(8010);

  return 0;
}
