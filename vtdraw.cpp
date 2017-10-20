#include <QApplication>
#include <QWidget>
#include <QLayout>

#include "main_window.hpp"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  if (argc <= 2) {
    if (argc == 2) {
		MainWindow example(argv[1]);
        example.show();
        return app.exec();
    }
    MainWindow example;
    example.show();
    return app.exec();
  }
  std::cout << "Error: Invalid number of arguments for 'vtdraw'" << std::endl;
  return -1;
}