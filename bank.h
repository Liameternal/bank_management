//
// Created by liam on 9/11/21.
//

#ifndef BANK_MANAGEMENT_BANK_H
#define BANK_MANAGEMENT_BANK_H

// Allow 15 character of username
#define NAME_LEN 16
// Allow 20 character of passed
#define PASS_LEN 21
//#define DEBUG
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

Status CreateBank(void);

Status ListBank(void);

Status DeleteBank(void);

Status AlterBank(void);

#endif//BANK_MANAGEMENT_BANK_H
