#include "lib/lpopts.h"

int hello(int argc, char **argv)
{
  option_t opts;

  next_option(argc, argv, &opts); // Get first option

  //printf("Hello! %d\n", argc);

  //printf("%c\n", opts.opt);

  next_option(argc, argv, &opts);

  //printf("%s, %s\n", opts.string, opts.arg);

  return 0;
}

int gb(int argc, char **argv)
{
  printf("Goodbye %d\n", argc);
  return 0;
}

int usage(int argc, char **argv)
{
  print_default_usage_message();
}

int main(int argc, char **argv)
{
  command_t commands[] = 
    { 
      { "hello", &hello }, 
      { "goodbye", &gb },
      { "help", &usage },
      { NULL  , NULL }
    };
  
  ci_register_cmds(commands);

  int exit_status = ci_main(argc, argv);

  return exit_status;
}