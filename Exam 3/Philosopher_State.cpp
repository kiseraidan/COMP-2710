// Aidan Kiser

Philosopher_State {

    Semaphore EatAgain[5];
    Semaphore mutex;
    int state[5];
    int p;

    take_chopsticks() {
        mutex.P(;
        state[p] = HUNGRY;
        test(p);
        mutex.V();
        EatAgain[p].P();
    }

    put_chopsticks() {
        mutex.P();
        state[p] = THINKING;
        test[(p+1)%5];
        test[(p+4)%5];
        mutex.V();
    }

    test(int i) {
        if (state[i] == HUNGRY && state[(i+1) % 5] != EATING && state[(i+4) % 5] != EATING) {
            state[i] = EATING;

            EatAgain[i].V();
        }
    }
}