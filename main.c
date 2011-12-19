#include "lib/lpopts.h" /* must include header for types */

/*  hello, gb, and usage are callbacks - they are called when 
*   their respective commands are entered. Callbacks must have the prototype
*   int func(int argc, char **argv). they act as a main method for the program
*   so option processing and anything else would take place in these, most likely.
*/

int hello(int argc, char **argv)
{
  option_t opts;
  /*  option_t looks like:
  *   struct option
  *     {
  *       char opt;       A character representing the option
  *       lp_str arg;     Any argument given to the option
  *       lp_str string;  A string, in the case of a long option
  *       char set;       A boolean, TRUE if the option is set
  *     };
  *   
  */

  while (next_option(argc, argv, &opts) != OPT_DONE)
    {
      printf("Opt: %c Arg: %s\n", opts.opt, opts.arg);
    }
  printf("After opts: %s\n", argv[optind]);

  return 0;
}

int gb(int argc, char **argv)
{
  printf("Goodbye %d\n", argc);
  return 0;
}

int usage(int argc, char **argv)
{
  /*  This function generates a default, somewhat helpful usage message using
  *   the available commands.
  */

  print_default_usage_message();
}

int main(int argc, char **argv)
{
  /*  A command_t struct just takes the name of the command and the function pointer
  *   to the callback, or the "main function" for that command. This is an array of
  *   them that will be passed to the register function. Note the last entry is NULL
  *   - this is used by lpopts to determine where the last command is. You must have
  *   an entry in the command array with a NULL name, or the command processor won't
  *   know when to stop.
  */
  command_t commands[] = 
    { 
      { "hello", &hello }, 
      { "goodbye", &gb },
      { "help", &usage },
      { NULL  , NULL }
    };
  
  /*  This makes lpopts aware of the commands. */

  ci_register_cmds(commands);

  /*  ci_main is the main function for the command interface. When called, it checks
  *   to see if a command given on the command line matches any of the commands that
  *   have been registered. It will return the return value of the callback function
  *   unless either no command was entered, or an unrecognized one was, in which case
  *   it will return 1.
  */

  int exit_status = ci_main(argc, argv);

  return exit_status;
}