def unique(X):
    U = dict()
    for x in X:
        U[x] = x
    return list(U.values())

if __name__ == "__main__":
    print(unique([1, 2, 3, 1, 2, 2, 5, 3]))
