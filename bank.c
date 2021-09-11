//
// Created by liam on 9/11/21.
//

#include <signal.h>
#include <stdio.h>
/*
 * For linux terminal,reference: https://psychocod3r.wordpress.com/2019/02/25/how-to-get-the-dimensions-of-a-linux-terminal-window-in-c/
 */
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "bank.h"

#define MENU_BAR 7

const char* menu_entries[MENU_BAR] = {
  "Welcome to bank management",
  "1) Create bank",
  "2) List bank",
  "3) Delete bank",
  "4) Alter bank",
  "5) Quit",
  "Enter a number before the function you want to use:"};

/*
 * Defined in sys/ioctl.h
 * struct winsize
 * {
 *   unsigned short int ws_row;
 *   unsigned short int ws_col;
 *   unsigned short int ws_xpixel;
 *   unsigned short int ws_ypixel;
 * };
 */
struct winsize sz;

static void GetWinSizeInfo(void);

static void EatLine(void);

static void ReDraw(void);

int Menu(void) {
  int ans;

  signal(SIGWINCH, (void*) ReDraw);
  ReDraw();
  scanf("%d", &ans);
  EatLine();
#ifdef DEBUG
  printf("Your answer is %d\n", ans);
  getchar();
#endif

  return ans;
}

static void GetWinSizeInfo(void) {
  ioctl(0, TIOCGWINSZ, &sz);
}

static void EatLine(void) {
  while (getchar() != '\n')
    continue;
}

static void ReDraw(void) {
  int left_space;
  int right;


  system("clear");
  GetWinSizeInfo();
  left_space = (sz.ws_col - strlen(menu_entries[0])) / 2;
  right = sz.ws_col - left_space - strlen(menu_entries[0]);
  for (int i = 0; i < MENU_BAR; ++i) {
    if (i == 0) {
      for (int j = 0; j < left_space; ++j) {
        putchar('*');
      }
      printf("%s", menu_entries[i]);
      for (int j = 0; j < right; ++j) {
        putchar('*');
      }
      puts("\n");
    } else {
      if (i != MENU_BAR - 1) {
        for (int j = 0; j < left_space; ++j) {
          putchar(' ');
        }
        printf("%s", menu_entries[i]);
        puts("\n");
      } else {
        printf("%s", menu_entries[i]);
        fflush(stdout);
      }
    }
  }
}

Status CreateBank(void) {
  return 1;
}

Status ListBank(void) {
  return 1;
}

Status DeleteBank(void) {
  return 1;
}

Status AlterBank(void) {
  return 1;
}
