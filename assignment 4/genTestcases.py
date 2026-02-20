import random

def generate_one_testcase():
    K = random.randint(2, 6)

    prices = []
    for i in range(K):
        price = random.randint(5, 40)
        prices.append(price)

    prices.sort()

    num_vehicles = random.randint(3, 6)

    vehicles = []

    for i in range(num_vehicles):
        arrival = random.randint(0, 20)
        departure = arrival + random.randint(5, 20)
        charge_time = random.randint(2, 15)

        vehicles.append((i + 1, arrival, departure, charge_time))

    return K, prices, vehicles


def generate_testcases(t):

    file = open("input.txt", "w")

    file.write(str(t))
    file.write("\n")

    for i in range(t):

        K, prices, vehicles = generate_one_testcase()

        file.write(str(K))
        file.write("\n")

        for p in prices:
            file.write(str(p) + " ")
        file.write("\n")

        file.write(str(len(vehicles)))
        file.write("\n")

        for v in vehicles:
            file.write(str(v[0]) + " " + str(v[1]) + " " + str(v[2]) + " " + str(v[3]))
            file.write("\n")

    file.close()


if __name__ == "__main__":
    t = int(input("Enter number of test cases: "))
    generate_testcases(t)
    print("input.txt generated successfully.")