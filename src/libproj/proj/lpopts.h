/*  libproj - Library of common programmatical functions
*   this file is part of libproj.
*   lpopts.h - defines functions and macros for processing options
*   Also defines an easy implementation for a command-type program, like git
*   Created on December 13, 2011
*/

#ifndef LIBPROJ
# define LIBPROJ
#endif

#ifndef LPOPTS_H

#define LPOPTS_H

#ifndef LPBASE
# include "base.h"
#endif

#ifndef LPERROR_H
# include "error.h"
#endif

#ifndef LPINIT_H
# include "init.h"
#endif

/* Errors */

#define E_UNREC  0x2A /* 0010 1010 Num = 10 Print = 1 Exit = 0 */

#define E_NOCMD	  0x32 /* 0011 0011 Num = 12 Print = 1 Exit = 0 */	

/* End Errors */

#define OPT_DONE -1

/*  Struct for a single command. Usually an array of these will be passed
*   to the register function. The name_str is the name of the command, and
*   what will be used to call the command from the command line. The second
*   member, func_ptr is a function pointer, as the name suggests, with the
*   prototype int func(int argc, lp_str *argv), similar to a regular main
*   function. The function pointed to by func_ptr will be called as the final
*   result of ci_main. Usually one would save the result of ci_main and return
*   it from their main function. ci_main normally returns the return value
*   of func_ptr for whichever command was called. The only exceptions are when
*   no command is entered, or when an unrecognized command is entered, in which
*   case it errors and prints messages that can be user-defined and returns 1.
*/

struct command
  {
    lp_str name_str;
    int (*func_ptr)(int argc, lp_str* argv);
  };

typedef struct command command_t;

/*  Struct for a single commandline option. opt is the short option, or
*   single character option. Arg is any argument that goes with it. String
*   is the long option, preceded by "--". If string is set, opt is 0 and vise-
*   versa. Set is just a boolean flag telling whether or not the option is set.
*/

struct option
  {
    char opt;
    lp_str arg;
    lp_str string;
    char set;
  };

typedef struct option option_t;

extern lp_str no_cmd_message;

extern lp_str unrecognized_cmd_message;

extern int processed_cmd;

extern lp_str usage_message;

extern command_t *registered_commands;

extern int option_done;

extern int number_commands;

int optind;

extern void ci_init(int num_cmds);

/*  The main method for constructing a command interface. This is usually called
*   last, after registering commands and doing any processing needed. In a main()
*   function, you can just return this if you don't have anything to do after the
*   commands exit. It will return whatever your command returns, unless there's an
*   error. This passes a decremented argc to your command, because your command is
*   being treated as the program name. It shifts argv completely to the left, removing
*   the original program name (although it can be saved) so that option processing
*   goes as expected.
*/

extern int ci_main(int argc, lp_str *argv);

extern void ci_register_commands(command_t *commands);

/*  Retrieves data about the next command line option, starting with the first one
*   passed. Puts information in fill, which is a struct option. Will process both
*   long and short option styles; sets the unused member to 0 or NULL.
*/

extern int next_option(int argc, lp_str *argv, option_t *opts);

/*  Sets the message that will be printed when no command is entered. */

extern void set_no_cmd_message(lp_str message);

/*  Sets the usage message for your program. */

extern void set_usage_message(lp_str message);

/*  Based on your registered commands, generates a (pretty unhelpful) usage message
*   that just consists of the possible commands.
*/

extern void print_default_usage_message(void);

/*  Internal function used to move argv one to the left, shifting the zeroth element
*   off.
*/

static void shift_argv(int argc, lp_str *argv);

#endif /* LPOPTS_H */