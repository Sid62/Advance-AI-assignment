from z3 import *

def solve_case(K, prices, vehicles):

    n = len(vehicles)

    port = []
    start = []
    duration = []

    for i in range(n):
        port.append(Int("port_" + str(i)))
        start.append(Int("start_" + str(i)))
        duration.append(Int("duration_" + str(i)))

    opt = Optimize()

    for i in range(n):

        ai = vehicles[i][0]
        di = vehicles[i][1]
        ci = vehicles[i][2]

        opt.add(port[i] >= 1)
        opt.add(port[i] <= K)

        opt.add(start[i] >= ai)

        opt.add(duration[i] * port[i] >= ci)
        opt.add(duration[i] * port[i] < ci + port[i])

        opt.add(start[i] + duration[i] <= di)

    for i in range(n):
        for j in range(i + 1, n):

            condition = Implies(
                port[i] == port[j],
                Or(
                    start[i] + duration[i] <= start[j],
                    start[j] + duration[j] <= start[i]
                )
            )

            opt.add(condition)

    cost_terms = []

    for i in range(n):

        price_expr = prices[0]

        for k in range(1, K):
            price_expr = If(port[i] == k + 1, prices[k], price_expr)

        cost_terms.append(duration[i] * price_expr)

    total_cost = Sum(cost_terms)

    opt.minimize(total_cost)

    if opt.check() == sat:

        model = opt.model()

        print("Total Cost:", model.evaluate(total_cost))

        for i in range(n):
            print("Vehicle", i + 1,
                  "Port:", model[port[i]],
                  "Start:", model[start[i]],
                  "Duration:", model[duration[i]])
    else:
        print("No feasible schedule")


def main():

    file = open("input.txt", "r")
    lines = file.readlines()
    file.close()

    index = 0
    t = int(lines[index].strip())
    index += 1

    for case_number in range(t):

        print("\n--- Test Case", case_number + 1, "---")

        K = int(lines[index].strip())
        index += 1

        prices = list(map(int, lines[index].split()))
        index += 1

        num_vehicles = int(lines[index].strip())
        index += 1

        vehicles = []

        for i in range(num_vehicles):
            parts = list(map(int, lines[index].split()))
            vehicles.append((parts[1], parts[2], parts[3]))
            index += 1

        solve_case(K, prices, vehicles)


if __name__ == "__main__":
    main()