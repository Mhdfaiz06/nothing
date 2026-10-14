/*Mohammed Faiz
S7 CSB 23
Exp 8
NFA to DFA transition*/
#include <stdio.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 5
#define MAX_DFA_STATES 100

int nfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
int dfa[MAX_DFA_STATES][MAX_SYMBOLS];

int n, symbols;
int dfaStates[MAX_DFA_STATES][MAX_STATES];
int dfaCount = 0;

/* Check whether a DFA state already exists */
int findState(int state[]) {
    for (int i = 0; i < dfaCount; i++) {
        int same = 1;

        for (int j = 0; j < n; j++) {
            if (dfaStates[i][j] != state[j]) {
                same = 0;
                break;
            }
        }

        if (same)
            return i;
    }

    return -1;
}

/* Find the DFA state reached using a symbol */
void move(int current[], int symbol,
          int result[]) {
    memset(result, 0, sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        if (current[i]) {
            for (int j = 0; j < n; j++) {
                if (nfa[i][symbol][j])
                    result[j] = 1;
            }
        }
    }
}

/* Print a set of states */
void printSet(int state[])
{
    printf("{");

    int first = 1;

    for (int i = 0; i < n; i++) {
        if (state[i]) {
            if (!first)
                printf(",");
            printf("q%d", i);
            first = 0;
        }
    }

    printf("}");
}

int main() {
    int transitions, from, to, symbol;
    int startState;

    printf("Enter number of NFA states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    printf("Enter number of NFA transitions: ");
    scanf("%d", &transitions);

    memset(nfa, 0, sizeof(nfa));

    printf("\nEnter transitions:\n");
    printf("Format: from_state symbol to_state\n");
    printf("States are 0 to %d\n", n - 1);
    printf("Symbols are numbered 0 to %d\n\n",
           symbols - 1);

    for (int i = 0; i < transitions; i++) {
        scanf("%d %d %d", &from, &symbol, &to);
        nfa[from][symbol][to] = 1;
    }

    printf("\nEnter start state: ");
    scanf("%d", &startState);

    /* Initial DFA state = {NFA start state} */
    memset(dfaStates[0], 0, sizeof(dfaStates[0]));
    dfaStates[0][startState] = 1;
    dfaCount = 1;

    /* Subset construction */
    for (int current = 0; current < dfaCount;
         current++) {

        for (symbol = 0; symbol < symbols;
             symbol++) {

            int newState[MAX_STATES];

            move(dfaStates[current], symbol,
                 newState);

            int index = findState(newState);

            if (index == -1) {
                index = dfaCount;

                for (int j = 0; j < n; j++)
                    dfaStates[index][j] = newState[j];

                dfaCount++;
            }

            dfa[current][symbol] = index;
        }
    }

    /* Display DFA */
    printf("\n\n========== DFA TRANSITION TABLE"
           " ==========\n");

    printf("\nDFA State\t");
    for (int i = 0; i < symbols; i++)
        printf("Symbol %d\t", i);

    printf("\n-----------------------------------"
           "--------\n");

    for (int i = 0; i < dfaCount; i++) {
        printSet(dfaStates[i]);
        printf("\t\t");

        for (int j = 0; j < symbols; j++) {
            printf("D%d\t\t", dfa[i][j]);
        }

        printf("\n");
    }

    printf("\nDFA states:\n");

    for (int i = 0; i < dfaCount; i++) {
        printf("D%d = ", i);
        printSet(dfaStates[i]);
        printf("\n");
    }

    printf("\nDFA start state: D0\n");

    return 0;
}

/*
Commands to run:
gcc <file_name>.c -o <file_name>
./<file_name>
*/
