// version and soft name
static const char version[] = "2.0 RC1";
static const char uname[] = "rpn v2.0 RC1, (c) 2013 <louis@rubet.fr>, GNU General Public License";

static const char g_cursor[] = "> ";
static const string g_show_stack_separator = "> ";

// syntax
static const char* syntax[] = {
    ATTR_BOLD "R" ATTR_OFF "everse "
    ATTR_BOLD "P" ATTR_OFF "olish "
    ATTR_BOLD "N" ATTR_OFF "otation language, based on Hewlett-Packard RPL",
    "",
    "Syntax: rpn [command]",
    "with optional command = list of commands",
    NULL
};

static const char prompt[] = ATTR_BOLD "rpn" ATTR_OFF "> ";
