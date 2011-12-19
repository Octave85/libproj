/*  libproj - Library of common programmatical functions
*   this file is part of libproj.
*   lpopts.c - defines functions and macros for processing options
*   Also defines an easy implementation for a command-type program, like git
*   Created on December 13, 2011
*/
#include <config.h>
#include <lpopts.h>

#define THIS_FILE "lpopts"

lp_str unrecognized_cmd_message = "No command found";

lp_str no_cmd_message = "No command entered";

lp_str usage_message;

lp_str _command;

command_t *registered_commands = NULL;

int processed_cmd = 0;

int option_done = 0;

int optind;

int number_commands = 0;

void set_unrecognized_cmd_message(lp_str message)
{
  assert(message != NULL);
  
  unrecognized_cmd_message = message;
}

void set_no_cmd_message(lp_str message)
{
  assert(message != NULL);
  
  no_cmd_message = message;
}

void print_default_usage_message(void)
{
  unsigned int i;

  char done = 0;
  printf("%s v%s\n", _essential_data.title, _essential_data.version);
  puts("Available commands:");

  while (! done)
    {
      if (i == number_commands)
        done = 1;
      else
        printf("\t%s\n", registered_commands[i].name_str);

      i++;
    } 
  
  fflush(stdout);
}

static void shift_argv(int argc, lp_str *argv)
{
  lp_str prog_name = argv[0];

  argv[0] = argv[1];

  int i = 1;

  for (i = 1; i < argc - 1; i++)
    argv[i] = argv[i + 1];
}

void ci_init(int num_cmds)
{
  number_commands = num_cmds;
}

void ci_register_commands(command_t *commands)
{
  registered_commands = commands;
}

int ci_main(int argc, lp_str *argv)
{ 
  unsigned int i = 0;
  
  static int ok = 1;

  if (argc < 2)
    {
      lp_error(E_NOCMD, no_cmd_message, _essential_data.title);
      return 1;
    }
    

  while (1)
    {
      if (i == number_commands)
        {
          ok = 0;
          break;
        }
      
      if (strncmp(argv[1], registered_commands[i].name_str, 
        strlen(argv[1])) == 0)
          break;
     
      i++;
    }

  if (!ok)
    {
      lp_error(E_UNREC, unrecognized_cmd_message, _essential_data.title);
      return 1;
    }
  
  processed_cmd = 1;

  shift_argv(argc, argv);

  _command = registered_commands[i].name_str;

  return (*registered_commands[i].func_ptr)(argc - 1, argv);

}

int next_option(int argc, lp_str *argv, option_t *fill)
{
  int optcount = 0;

  static char opt_found = 0;

  static unsigned int i = 1;


  if (! option_done && i < argc && argv[i][0] == '-')
    {
      switch (argv[i][1])
        {
          case '-':
            if (argv[i][2] == '\0')
              {
                option_done = 1;
                
                optind = i + 1;
                return OPT_DONE;
              }
            else
              {
               opt_found = 1;
               fill->string = malloc(strlen(argv[i] - 1));

               strcpy(fill->string, argv[i] + 2);
              
               fill->opt = 0;

               fill->set = 1; 
              }

            break;
          default:
            opt_found = 1;
            fill->opt = argv[i][1];

            fill->set = 1;

            fill->string = NULL;

            break;
        }

      if (i + 1 < argc && argv[i + 1][0] != '-')
        {
          fill->arg = argv[i + 1];

          i++;
        }
      else
        {
          fill->arg = NULL;
        }
              
      optcount++;

      i++;
      
      return 1;
    }
  
  if (option_done || fill->arg != NULL)
    optind = i + 1;
  else if (!opt_found)
    optind = 1;
  else
    optind = i;
  
  return OPT_DONE;
}