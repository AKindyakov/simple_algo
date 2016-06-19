import eratosthensSieve

def test_get_all_prime_0():
    assert list(eratosthensSieve.get_all_prime(0)) == []

def test_get_all_prime_1():
    assert list(eratosthensSieve.get_all_prime(1)) == [1]

def test_get_all_prime_2():
    assert list(eratosthensSieve.get_all_prime(2)) == [1, 2]

def test_get_all_prime_4():
    assert list(eratosthensSieve.get_all_prime(4)) == [1, 2, 3]
