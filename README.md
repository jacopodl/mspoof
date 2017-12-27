![](https://img.shields.io/badge/Language-C-orange.svg)
![](https://img.shields.io/badge/version-1.7.0-green.svg)
[![GPLv3 License](https://img.shields.io/badge/license-GPL3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0.html)


# ArgsX #
Argsx is a easy to use command line option parser for C/C++ that support long and short option formats.

# Overview #
## Long option interface ##
```c++
struct ax_lopt {
    char *name;	// Option
    int args;	// Required parameter ?
    char opt;	// Return value
}

struct ax_lopt longOpt[] = {{"one", ARGSX_NOARG, 1},
			    {"two", ARGSX_REQ_ARG, 2},
			    {"three", ARGSX_NOARG, 't'}};
```
## Short option ##
Short option required string formatted in this way:
1. Single character like 'l' -> Option that dosn't require additional parameter.
1. Single character followed by ! like 't!' -> Option that require additional parameter.

For example, if your program require options 'a','b','c' without parameter and option 't' and 'e' with parameter you can write string like this: "abct!e!".

## ArgsX function ##
```c++
    int ArgsX(
	int argc,                   // argc parameter
	char **argv,                // argv parameter
	char *opt,                  // pointer to short options string
	ax_lopt *lopt,              // pointer to long options struct
	unsigned short lopt_size,   // size of long options struct
	char tr                     // Trigger char Eg: '-'
	);
```
## Put all together ##
```c++
struct ax_lopt longOpt[] = {{"one", ARGSX_NOARG, 1},
			    {"two", ARGSX_REQ_ARG, 2},
			    {"three", ARGSX_NOARG, 't'}};
    int opt;
    while((opt = ArgsX(argc, argv, "abct!e!", longOpt, sizeof(longOpt), '-')) != -1)
    {
      switch(opt)
      {
      	case 1:
	// --one
	break;
	case 2:
	// --two
	break;
        case 'a':
        break;
	case 'b':
        break;
        case 't':
        // -t or --three
        break;
        case ARGSX_BAD_OPT:
        break;
        case ARGSX_FEW_ARGS:
        break;
        case ARGSX_NONOPT:
        break;
      }
    }
```
