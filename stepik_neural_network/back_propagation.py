import numpy as np 


def sigmoid(x):
    return 1.0/(1 + np.exp(-x))

def sigmoid_prime(x):
    return sigmoid(x)*(1 - sigmoid(x))

def evaluate_dJ_dw_2_3(x, w2, w3, y):
    """ 
    x - input data
    w2 - weights of second layer
    w3 - weights of third layer
    y - true output
    """
    z2 = w2.T.dot(x)
    a2 = sigmoid(z2)

    z3 = w3.T.dot(a2)
    a3 = sigmoid(z3)

    delta3 = (a3 - y) * sigmoid_prime(z3)
    delta2 = (w3.dot(delta3)) * sigmoid_prime(z2)

    dJ_dw = x.dot(delta2.T)
    return dJ_dw

x = np.array([[0.0],
              [1.0],
              [2.0]])
w2 = np.array([[2.0, 2.0],
                [2.0, 2.0],
                [2.0, 2.0]])
w3 = np.array([[1.0],
                [1.0]])

y = np.array([1.0])

print(evaluate_dJ_dw_2_3(x, w2, w3, y))

w2 = np.array([[8.0, 10.0],
                [7.0, 10.0],
                [8.0, 9.0]])
w3 = np.array([[10.0],
                [9.0]])
print(evaluate_dJ_dw_2_3(x, w2, w3, y))

w2 = np.array([[8.0, 10.0],
                [7.0, 10.0],
                [8.0, 9.0]])
w3 = np.array([[10.0],
                [9.0]])
print(evaluate_dJ_dw_2_3(x, w2, w3, y))


def evaluate_dJ_dw_2_3_with_other_act_func(x, w2, w3, y):
    """ 
    x - input data
    w2 - weights of second layer
    w3 - weights of third layer
    y - true output
    """
    z2 = w2.T.dot(x)
    a2 = sigmoid(z2)
    a2[0][0] = max(z2[0][0], 0.0)

    z3 = w3.T.dot(a2)
    a3 = sigmoid(z3)

    delta3 = (a3 - y) * sigmoid_prime(z3)
    prime = np.array([[int(z2[0][0] > 0)], [sigmoid_prime(z2[1][0])]])
    delta2 = (w3.dot(delta3)) * prime

    dJ_dw = x.dot(delta2.T)
    return dJ_dw


x = np.array([[0.0],
              [1.0],
              [1.0]])
w2 = np.array([[0.7, 0.8],
                [0.2, 0.3],
                [0.7, 0.6]])
w3 = np.array([[0.2],
                [0.4]])
y = np.array([[1]])

print(evaluate_dJ_dw_2_3_with_other_act_func(x, w2, w3, y))