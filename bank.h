//
// Created by liam on 9/11/21.
//

#ifndef BANK_MANAGEMENT_BANK_H
#define BANK_MANAGEMENT_BANK_H

// Allow 15 character of username
#define NAME_LEN 16
// Allow 20 character of passed
#define PASS_LEN 21
/*
 * Set DEBUG mode
 * Uncomment this will make blocks surrounded by #define DEBUG work
 */
//#define DEBUG

/*
 * Set linux terminal mode
 * Uncomment this will make blocks surrounded by #define LINUX_TERMINAL work
 */
#define LINUX_TERMINAL

typedef int Status;
typedef struct {
  char username[NAME_LEN];
  char passwd[PASS_LEN];
} Bank;

/*
 * Show menu
 * Accept nothing
 * Return a number which is the function you chose
 */
int Menu(void);

void Wait(void);

Status Initialize(Bank *bank);

Status CreateBank(Bank* bank);

Status ListBank(const Bank* bank);

Status DeleteBank(Bank* bank);

Status AlterBank(Bank* bank);

Status Quit(const Bank* bank);

#endif//BANK_MANAGEMENT_BANK_H
