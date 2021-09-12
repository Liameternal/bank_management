#include "bank.h"
#include <stdbool.h>
#include <stdio.h>

extern int CAPACITY;
int main() {
  bool quit = false;
  Bank bank[CAPACITY];
  Initialize(bank);

  while (!quit) {
    switch (Menu()) {
      case 1:
        CreateBank(bank);
        break;
      case 2:
        ListBank(bank);
        Wait();
        break;
      case 3:
        DeleteBank(bank);
        break;
      case 4:
        AlterBank(bank);
        break;
      case 5:
        Quit(bank);
        quit = true;
        break;
      default:
        printf("Enter a number before function\n");
    }
  }

  return 0;
}
