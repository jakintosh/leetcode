int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int start = 0, tank = 0, total = 0;
    for (int i = 0; i < gasSize; i++) {
        int net = gas[i] - cost[i];
        tank = tank + net;
        total = total + net;
        if (tank < 0) {
            tank = 0;
            start = i + 1;
        }
    }
    return (total >= 0) ? start : -1;
}
