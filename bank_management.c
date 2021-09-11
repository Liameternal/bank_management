#include "bank.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
  bool quit = false;

  while (!quit) {
    switch (Menu()) {
      case 1:
        CreateBank();
        break;
      case 2:
        ListBank();
        break;
      case 3:
        DeleteBank();
        break;
      case 4:
        AlterBank();
        break;
      case 5:
        quit = true;
        break;
      default:
        printf("Enter a number before function\n");
    }
  }

  return 0;
}
