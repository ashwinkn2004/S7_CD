#include <stdio.h>

struct TRANSITION {
    int from;
    int to;
    char input;
} transitions[50];

int states, transition;

int isPresent(int arr[], int size, int val) {
    for (int i = 0; i < size; i++)
        if (arr[i] == val)
            return 1;
    return 0;
}

void epsilonClosure(int state) {
    int closure[50], top = 0;
    closure[top++] = state;

    for (int i = 0; i < top; i++) {
        int curr = closure[i];
        for (int j = 0; j < transition; j++) {
            if (transitions[j].from == curr && transitions[j].input == 'e') {
                int next = transitions[j].to;
                if (!isPresent(closure, top, next)) {
                    closure[top++] = next;
                }
            }
        }
    }

    printf("closure(q%d) = { ", state);
    for (int i = 0; i < top; i++) {
        printf("q%d ", closure[i]);
    }
    printf("}\n");
}

void main() {
    printf("Enter the number of states: ");
    scanf("%d", &states);
    printf("Enter the number of transitions: ");
    scanf("%d", &transition);

    printf("Enter the transitions:\n");
    for (int i = 0; i < transition; i++) {
        printf("FROM: ");
        scanf("%d", &transitions[i].from);
        printf("TO: ");
        scanf("%d", &transitions[i].to);
        printf("INPUT: ");
        scanf(" %c", &transitions[i].input);
    }

    printf("\nTRANSITIONS:\n");
    for (int i = 0; i < transition; i++) {
        printf("q%d -> q%d = { %c }\n", transitions[i].from, transitions[i].to, transitions[i].input);
    }

    printf("\nEPSILON CLOSURES:\n");
    for (int i = 0; i < states; i++) {
        epsilonClosure(i);
    }
}
