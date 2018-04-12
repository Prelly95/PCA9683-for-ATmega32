#include <stdio.h>
#include <stdlib.h> // atoi
#include <ctype.h>
#include <string.h>
#include <inttypes.h> // For PRIxx and SCNxx macros
#include <avr/pgmspace.h>
#include "cmd_line_buffer.h"
#include "cmd_parser.h"

static void _cmd_help(void);

void cmd_parse(const char * cmd)
{
    if (cmd == NULL)
    {
        printf_P(PSTR("ERROR: Tried to parse NULL command pointer\n"));
    }
	else if (!strncmp_P(cmd, PSTR("clear"), 5) || !strncmp_P(cmd, PSTR("clc"), 3))
	{
		printf_P(PSTR("\014"));
	}
    else if (*cmd == '\0') // Empty command string
    {
        return;
    }
    else if (!strncmp_P(cmd, PSTR("help"), 4))
    {
        _cmd_help();
    }
    else
    {
        printf_P(PSTR("Unknown command: \"%s\"\n"), cmd);
    }
}

void _cmd_help(void)
{
    printf_P(PSTR(
        "\n"
        "\n"
    ));

    printf_P(PSTR("\n"));

    // Describe argument syntax using POSIX.1-2008 convention
    // see http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap12.html
    printf_P(PSTR(
        "Available commands:\n"
		"    clear or clc               Clears the current serial terminal (Handle Form Feed characters must be enabled)"
        "\n"
    ));
}
