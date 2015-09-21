#include <iostream>
#include <application/application.hpp>

int main(int argc, char ** argv)
{
	express::application app;

    app.get("/hello",[](express::request req, express::response res) {
      res.send("World !");
    });

    app.listen(80);

  return 0;
}
