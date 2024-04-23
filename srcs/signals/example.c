#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sig) {
    printf("Received signal: %d\n", sig);
    if (sig == SIGINT || sig == SIGQUIT) {
        printf("Exiting program.\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        perror("signal");
        return EXIT_FAILURE;
    }

    if (signal(SIGQUIT, sig_handler) == SIG_ERR) {
        perror("signal");
        return EXIT_FAILURE;
    }

    printf("Send SIGINT (Ctrl+C) or SIGQUIT (Ctrl+\\) to trigger the signal handlers.\n");

    while (1) {
        sleep(1);
    }

    return EXIT_SUCCESS;
}
