//concatenates reg[idx0] with reg[idx1] and puts it in reg[idx0]
__declspec(dllexport)void concat_2(State *state, char *idx0, char *idx1);
//extracts sequence of tokens/words separated by underscore character from string [arg]
//puts K –- number of tokens into 0-th register
//puts the tokens into 1-th, 2-th, ..., K-th registers (in correct order)
__declspec(dllexport)void tokenize_1(State *state, char *arg);