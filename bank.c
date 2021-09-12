//
// Created by liam on 9/11/21.
//

#include "bank.h"
#include <signal.h>
#include <stdio.h>
/*
 * For linux terminal,reference: https://psychocod3r.wordpress.com/2019/02/25/how-to-get-the-dimensions-of-a-linux-terminal-window-in-c/
 */
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myhead/myself.h"

#define MENU_BAR 7
#define FILENAME "bank.dat"

int bank_account_num = 0;
#ifdef DEBUG
const int CAPACITY = 2;
#else
const int CAPACITY = 100;
#endif

const char* menu_entries[MENU_BAR] = {
  "Welcome to bank management",
  "1) Create bank",
  "2) List bank",
  "3) Delete bank",
  "4) Alter bank",
  "5) Quit",
  "Enter a number before the function you want to use:"};

#ifdef LINUX_TERMINAL
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

/*
 * Initialize sz
 */
static void GetWinSizeInfo(void);

/*
 * Clean remain characters
 */
#endif
static void EatLine(void);

/*
 * Draw menu
 */
static void ReDraw(void);

static int ReadData(Bank* b, FILE* fp);

static int WriteData(const Bank* b, FILE* fp);


int Menu(void) {
  int ans;

#ifdef LINUX_TERMINAL
  signal(SIGWINCH, (void*) ReDraw);
#endif
  ReDraw();
  scanf("%d", &ans);
  EatLine();

#ifdef DEBUG
  printf("Your answer is %d\n", ans);
  Wait();
#endif

  return ans;
}

#ifdef LINUX_TERMINAL
static void GetWinSizeInfo(void) {
  ioctl(0, TIOCGWINSZ, &sz);
}
#endif

static void EatLine(void) {
  while (getchar() != '\n')
    continue;
}

static void ReDraw(void) {
  int left_space;
  int right_asterisk;

  system("clear");
#ifdef LINUX_TERMINAL
  GetWinSizeInfo();
  left_space = (sz.ws_col - strlen(menu_entries[0])) / 2;
  right_asterisk = sz.ws_col - left_space - strlen(menu_entries[0]);
  for (int i = 0; i < MENU_BAR; ++i) {
    if (i == 0) {
      for (int j = 0; j < left_space; ++j) {
        putchar('*');
      }
      printf("%s", menu_entries[i]);
      for (int j = 0; j < right_asterisk; ++j) {
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
#else
  for (int i = 0; i < MENU_BAR; ++i) {
    if (i != MENU_BAR - 1)
      puts(menu_entries[i]);
    else
      printf("%s", menu_entries[i]);
  }
#endif
}

static int ReadData(Bank* b, FILE* fp) {
  if ((fp = fopen(FILENAME, "rb")) == NULL) {
    fprintf(stderr, "Can't open %s\n", FILENAME);
    exit(EXIT_FAILURE);
  }
  if (fread(&bank_account_num, sizeof(int), 1, fp) != 1) {
    fprintf(stderr, "Read bank account num failed\n");
    exit(EXIT_FAILURE);
  }
  if (fread(b, sizeof(Bank), bank_account_num, fp) != bank_account_num) {
    fprintf(stderr, "Read bank account failed\n");
    exit(EXIT_FAILURE);
  }
  printf("Read successfully\n");
  sleep(1);
  return 1;
}

static int WriteData(const Bank* b, FILE* fp) {
  if ((fp = fopen(FILENAME, "wb")) == NULL) {
    fprintf(stderr, "Can't open %s\n", FILENAME);
    exit(EXIT_FAILURE);
  }
  if ((fp = freopen(FILENAME, "ab", fp)) == NULL) {
    fprintf(stderr, "Can't reopen %s\n", FILENAME);
    exit(EXIT_FAILURE);
  }
  if (fwrite(&bank_account_num, sizeof(int), 1, fp) != 1) {
    fprintf(stderr, "Write bank account num failed\n");
    exit(EXIT_FAILURE);
  }
  if (fwrite(b, sizeof(Bank), bank_account_num, fp) != bank_account_num) {
    fprintf(stderr, "Write bank account failed\n");
    exit(EXIT_FAILURE);
  }
  printf("Write successfully\n");
  sleep(1);

  return 1;
}

Status Initialize(Bank* bank) {
  FILE* fp;

  ReadData(bank, fp);

  return 1;
}

Status CreateBank(Bank* bank) {
  Bank temp;

  if (bank_account_num < CAPACITY) {
    printf("Enter your bank account: ");
    StrGet(temp.username, NAME_LEN, stdin);
    printf("Enter you bank password: ");
    StrGet(temp.passwd, PASS_LEN, stdin);
    if (strcmp(temp.username, "") != 0 && strcmp(temp.passwd, "") != 0) {
      strcpy(bank[bank_account_num].username, temp.username);
      strcpy(bank[bank_account_num].passwd, temp.passwd);
      ++bank_account_num;
      return 1;
    } else {
      printf("Contain blank line, illegal\n");
      return 0;
    }
  } else {
    printf("Full of capacity\n");
    return 0;
  }
}

Status ListBank(const Bank* bank) {
  puts("****************************************");
  if (bank_account_num == 0) {
    printf("Nothing is here\n");
  }
  for (int i = 0; i < bank_account_num; ++i) {
    printf("%d# ", i + 1);
    printf("username: %s-----", bank[i].username);
    printf("password: %s\n", bank[i].passwd);
  }
  puts("****************************************");

  return 1;
}

Status DeleteBank(Bank* bank) {
  int index;
  Bank temp;

  ListBank(bank);
  printf("Which one do you want to delete: ");
  scanf("%d", &index);
  EatLine();
  if (index < 0 || index > bank_account_num) {
    printf("The one you chose is illegal\n");
    return 0;
  }
  if (index == bank_account_num) {
    --bank_account_num;
    return 1;
  }
  for (int i = index - 1; i < bank_account_num - 1; ++i) {
    temp = bank[i];
    bank[i] = bank[i + 1];
    bank[i + 1] = temp;
    --bank_account_num;
  }

  return 1;
}

Status AlterBank(Bank* bank) {
  int index;
  Bank temp;

  ListBank(bank);
  printf("Which one do you want to alter: ");
  scanf("%d", &index);
  EatLine();
  if (index < 0 || index > bank_account_num) {
    printf("The one you chose is illegal\n");
    return 0;
  }

  printf("Enter your bank account(New line to skip over): ");
  StrGet(temp.username, NAME_LEN, stdin);
  printf("Enter you bank password(New line to skip over): ");
  StrGet(temp.passwd, PASS_LEN, stdin);
  if (strcmp(temp.username, "") != 0)
    strcpy(bank[index - 1].username, temp.username);
  if (strcmp(temp.passwd, "") != 0)
    strcpy(bank[index - 1].passwd, temp.passwd);

  return 1;
}

void Wait(void) {
  printf("Press any key to continue...\n");
  getchar();
}

Status Quit(const Bank* bank) {
  FILE* fp;

  WriteData(bank, fp);
}
