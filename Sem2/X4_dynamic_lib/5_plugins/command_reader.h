//parses arguments of a function
//returns EOF or last character read
int parseArgs(Command *command);
//parses plugin and function names
//returns EOF or last character read
int parseInst(Command *command);
//parses a command for myasm
//returns EOF or last character read
int parseCommand(Command *command);