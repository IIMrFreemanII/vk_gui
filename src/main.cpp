#include "application.h"

int main() {
  Application application;
  application.init();
  application.run();
  application.cleanup();

  return 0;
}
