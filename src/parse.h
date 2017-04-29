// keywords declaration
struct keyword_t
{
    cmd_type_t type;
    char name[24];
    program_fn_t fn;
    string comment;
};
static const int g_max_commands = 128;
static keyword_t _keywords[g_max_commands];

static ret_value get_fn(const char* fn_name, program_fn_t& fn, cmd_type_t& type)
{
    for(unsigned int i=0; (i<sizeof(_keywords)/sizeof(_keywords[0])) && (_keywords[i].type != cmd_max); i++)
    {
        if ((strnlen(_keywords[i].name, sizeof(_keywords[i].name))>0)
            && (strncmp(fn_name, _keywords[i].name, sizeof(_keywords[i].name)) == 0))
        {
            fn = _keywords[i].fn;
            type = _keywords[i].type;
            return ret_ok;
        }
    }
    return ret_unknown_err;
}

static bool _cut(const char* entry, vector<string>& entries)
{
    string tmp;
    int len = strlen(entry);

    for (int i=0; i < len; i++)
    {
        switch(entry[i])
        {
            //symbol
            case '\'':
                //push prec entry if exists
                if (tmp.size() > 0)
                {
                    entries.push_back(tmp);
                    tmp.clear();
                }
                //get symbol
                tmp='\'';
                i++;
                while((i < len) && (isalnum(entry[i]) || entry[i]=='_'))
                    tmp += entry[i++];
                if ((i < len) && entry[i] == '\'')
                    tmp += '\'';
                entries.push_back(tmp);
                tmp.clear();
                break;

            //string
            case '"':
                //push prec entry if exists
                if (tmp.size() > 0)
                {
                    entries.push_back(tmp);
                    tmp.clear();
                }
                //get expression
                tmp='"';
                i++;
                while(i < len && entry[i] >= ' ')
                {
                    tmp += entry[i];
                    if (entry[i++] == '"')
                        break;
                }
                entries.push_back(tmp);
                tmp.clear();
                break;

            //program
            case '<':
                //push prec entry if exists
                if (tmp.size()>0)
                {
                    entries.push_back(tmp);
                    tmp.clear();
                }

                if (strncmp(&entry[i], "<<", 2) == 0)
                {
                    int up = 1;

                    // found a program begin
                    i += 2;
                    tmp = "<< ";

                    // trim leading spaces
                    while (i < len && (entry[i]==' ' || entry[i]=='\t'))
                        i++;

                    while(i < len)
                    {
                        if (strncmp(&entry[i], "<<", 2) == 0)
                        {
                            up++;
                            i += 2;
                            tmp += " << ";
                            // trim leading spaces
                            while (i < len && (entry[i] == ' ' || entry[i] == '\t'))
                                i++;
                        }
                        else if (strncmp(&entry[i], ">>", 2) == 0)
                        {
                            up--;
                            i += 2;
                            tmp += " >>";

                            // trim trailing spaces
                            while (i < len && (entry[i] == ' ' || entry[i] == '\t'))
                                i++;
                            // found end
                            if (up == 0)
                                break;
                        }
                        else
                        {
                            tmp += entry[i];
                            i++;
                        }
                    }
                    while((up--)>0)
                    {
                        tmp += " >>";
                    }
                    if (tmp.size()>0)
                    {
                        entries.push_back(tmp);
                        tmp.clear();
                    }
                    i--;// i has move 1 too far
                }
                else
                {
                    // reinject '<'' which is not a prog begin
                    tmp = "<";
                }
                break;

            //other
            default:
                if (entry[i] != ' ' && entry[i] != '\t')
                {
                    tmp += entry[i];
                }
                else
                {
                    if (tmp.size()>0)
                    {
                        entries.push_back(tmp);
                        tmp.clear();
                    }
                }
                break;
        }
    }
    if (tmp.size()>0)
    {
        entries.push_back(tmp);
        tmp.clear();
    }
    return entries.size()>0;
}

static bool get_keyword(const string& entry, program& prog, string& remaining_entry)
{
    program_fn_t fn;
    unsigned int obj_len;
    cmd_type_t type;
    bool ret = false;

    // could be a command
    if (get_fn(entry.c_str(), fn, type) == ret_ok)
    {
        if (type == cmd_keyword)
        {
            // allocate keyword object
            obj_len = sizeof(keyword)+entry.size()+1;
            keyword* new_obj = (keyword*)prog.allocate_back(obj_len, cmd_keyword);
            new_obj->set(fn, entry.c_str(), entry.size());
            ret = true;
        }
        else if (type == cmd_branch)
        {
            // allocate branch object
            obj_len = sizeof(branch)+entry.size()+1;
            branch* new_obj = (branch*)prog.allocate_back(obj_len, cmd_branch);
            new_obj->set((branch_fn_t)fn, entry.c_str(), entry.size());
            ret = true;
        }
    }

    return ret;
}

static bool get_symbol(const string& entry, program& prog, string& remaining_entry)
{
    bool ret = false;
    int entry_len = entry.size();
    unsigned int obj_len;

    if (entry_len>=1 && entry[0]=='\'')
    {
        // symbol entry, like 'toto'
        if (entry_len == 1)
        {
            // total object length
            obj_len = sizeof(symbol)+1;

            // allocate and set object
            symbol* new_obj = (symbol*)prog.allocate_back(obj_len, cmd_symbol);
            new_obj->set("", 0);
        }
        else
        {
            int naked_entry_len;

            // entry length without prefix / postfix
            naked_entry_len = entry[entry_len-1]=='\''?(entry_len-2):(entry_len-1);
            // total object length
            obj_len = sizeof(symbol)+naked_entry_len+1;

            // allocate and set object
            symbol* new_obj = (symbol*)prog.allocate_back(obj_len, cmd_symbol);
            new_obj->set(entry.substr(1, naked_entry_len).c_str(), naked_entry_len);
        }
        ret = true;
    }

    return ret;
}

static bool get_other(const string& entry, program& prog, string& remaining_entry)
{
    bool ret = false;
    int entry_len = entry.size();
    unsigned int obj_len;

    if (entry_len>=1)
    {
        // entry which is nothing is considered as an auto-evaluated symbol
        int naked_entry_len;

        // entry length without prefix / postfix
        naked_entry_len = entry[entry_len-1]=='\''?(entry_len-1):(entry_len);
        // total object length
        obj_len = sizeof(symbol)+naked_entry_len+1;

        // allocate and set object
        symbol* new_obj = (symbol*)prog.allocate_back(obj_len, cmd_symbol);
        new_obj->set(entry.c_str(), naked_entry_len);
        new_obj->_auto_eval = true;
        ret = true;
    }

    return ret;
}

static bool get_string(const string& entry, program& prog, string& remaining_entry)
{
    bool ret = false;
    unsigned int obj_len;
    int entry_len = entry.size();
    if (entry_len>=1 && entry[0]=='"')
    {
        if (entry_len == 1)
        {
            // total object length
            obj_len = sizeof(ostring)+1;

            // allocate and set object
            ostring* new_obj = (ostring*)prog.allocate_back(obj_len, cmd_string);
            new_obj->set("", 0);
        }
        else
        {
            int naked_entry_len;

            // entry length without prefix / postfix
            naked_entry_len = entry[entry_len-1]=='"'?(entry_len-2):(entry_len-1);

            // total object length
            obj_len = sizeof(ostring)+naked_entry_len+1;

            // allocate and set object
            ostring* new_obj = (ostring*)prog.allocate_back(obj_len, cmd_string);
            new_obj->set(entry.substr(1, naked_entry_len).c_str(), naked_entry_len);
        }
        ret = true;
    }

    return ret;
}

static bool get_program(const string& entry, program& prog, string& remaining_entry)
{
    bool ret = false;
    unsigned int obj_len;
    int entry_len = entry.size();
    if (entry_len>=2 && entry[0]=='<' && entry[1]=='<')
    {
        int naked_entry_len;

        // entry length without prefix / postfix
        if (entry_len>=4 && entry[entry_len-1]=='>' && entry[entry_len-2]=='>')
            naked_entry_len = entry_len-4;
        else
            naked_entry_len = entry_len-2;

        // total object length
        obj_len = sizeof(oprogram)+naked_entry_len+1;

        // allocate and set object
        oprogram* new_obj = (oprogram*)prog.allocate_back(obj_len, cmd_program);
        new_obj->set(&entry[2], naked_entry_len);

        ret = true;
    }
    return ret;
}

// care: not threadsafe
static bool get_float(const string& entry, program& prog, string& remaining_entry)
{
    char* endptr;
    bool ret = false;

    if (entry.size() > 0)
    {
        // pre parse to avoid doing a useless allocation
        // detect the begining of a number, including nan, inf, @nan@, @inf@
        if (entry.find_first_of("+-0123456789.ni@", 0) == 0)
        {
            void* significand;
            number* num = (number*)prog.allocate_back((unsigned int)sizeof(number), cmd_number, MPFR_128BITS_STORING_LENGTH, &significand);
            num->init(significand);

            int mpfr_ret = mpfr_strtofr(num->_value.mpfr, entry.c_str(), &endptr, 0, MPFR_DEF_RND);
            if (endptr != entry.c_str())
            {
                ret = true;
                // remaining string if any
                if (endptr != NULL)
                    remaining_entry = endptr;
            }
            else
                (void)prog.pop_back();
        }
    }

    return ret;
}

// care: not threadsafe
static bool get_binary(const string& entry, program& prog, string& remaining_entry)
{
    integer_t val;
    bool ret = false;

    if ((entry.size() >= 2) && (entry[0] == '#'))
    {
        stringstream token;
        char type = entry[entry.size() - 1];
        bool syntax;

        switch(type)
        {
            case 'd':
                token<<std::dec<<entry.substr(1);
                syntax = true;
                break;
            case 'h':
                token<<std::hex<<entry.substr(1);
                syntax = true;
                break;
            case 'o':
                token<<std::oct<<entry.substr(1);
                syntax = true;
                break;
            default:
                syntax = false;
                break;
        }

        token>>val;
        if(syntax && !token.fail())
        {
            binary* new_binary = (binary*)prog.allocate_back((unsigned int)sizeof(binary), cmd_binary);
            new_binary->set(val);
            ret = true;
        }
    }

    return ret;
}

static bool get_binary_bin(const string& entry, program& prog, string& remaining_entry)
{
    integer_t val;
    int len = entry.size();
    bool ret = false;
    
    if ((len > 2) && (entry[0] == '#') && (entry[len - 1] == 'b'))
    {
        integer_t val(0);
        integer_t exponent = (1 << (len-3));
        for(int i=0; i<(len-2); i++)
        {
            if (entry.at(i+1)=='1')
            {
                val+=exponent;
            }
            exponent>>=1;
        }

        binary* new_binary = (binary*)prog.allocate_back((unsigned int)sizeof(binary), cmd_binary);
        new_binary->set(val);
        ret = true;
    }

    return ret;
}

static bool _obj_from_string(const string& entry, program& prog, string& remaining_entry)
{
    bool ret = false;
    
    remaining_entry.erase();

    if (get_float(entry, prog, remaining_entry))
    {
        ret = true;
    }
    else if (get_binary(entry, prog, remaining_entry))
    {
        ret = true;
    }
    else if (get_binary_bin(entry, prog, remaining_entry))
    {
        ret = true;
    }
    else if (get_symbol(entry, prog, remaining_entry))
    {
        ret = true;
    }
    else if (get_string(entry, prog, remaining_entry))
    {
        ret = true;
    }
    else if (get_program(entry, prog, remaining_entry))
    {
        ret = true;
    }
    else if (get_keyword(entry, prog, remaining_entry))
    {
        ret = true;
    }
    else
    {
        // nothing, considered as an auto-evaluated symbol
        if (get_other(entry, prog, remaining_entry))
        {
            ret = true;
        }
    }

    return ret;
}

static char* entry_completion_generator(const char* text, int state)
{
    static int list_index, len, too_far;
 
    if (state == 0)
    {
        list_index = 0;
        too_far = 0;
        len = strlen(text);
    }
 
    while(too_far == 0)
    {
        list_index++;
        if (_keywords[list_index].fn != NULL)
        {
            // compare list entry with text, return if match
            if (strncmp(_keywords[list_index].name, text, len) == 0)
                return entry_completion_dupstr(_keywords[list_index].name);
        }
        else
        {
            // fn=NULL and size=0 = last entry in list -> go out
            if (_keywords[list_index].comment.size() == 0)
                too_far = 1;
        }
    }
 
    /* If no names matched, then return NULL. */
    return (char*)NULL;
 
}

static char* entry_completion_dupstr(char* s)
{
    char* r = (char*)malloc((strlen(s)+1));
    if (r != NULL)
        strcpy(r, s);
    return r;
}

static ret_value parse(const char* entry, program& prog)
{
    vector<string> entries;
    ret_value ret = ret_ok;

    //1. cut global entry string into shorter strings
    if (_cut(entry, entries))
    {
        //2. make an object from each entry, and add it to the program
        for (vector<string>::iterator it = entries.begin(); it != entries.end(); it++)
        {
            string remaining_entry;
            string main_entry = (*it);
            while(main_entry.size()>0)
            {
                // remaining_entry is used only in case of concatenated entry
                // ex:  entry="1 2+" -> vector<string> = {"1", "2+"} -> first "1", second "2" and remaining_entry="+"
                // this remaining entry is treated as an entry
                
                // TODO errors ?
                _obj_from_string(main_entry, prog, remaining_entry);
                main_entry = remaining_entry;
            }
        }
    }

    return ret;
}

// interactive entry and decoding
static ret_value entry(program& prog)
{
    char* buf;
    ret_value ret;

    // declare completion fn (bound to '\t' by default)
    rl_completion_entry_function = entry_completion_generator;

    // get user entry
    buf = readline(prompt);
    if (buf != NULL)
    {
        // parse it
        ret = parse(buf, prog);

        // keep history
        if (buf[0]!=0)
            add_history(buf);
    }
    else
        ret = ret_internal;

    //TODO
    free(buf);
}
