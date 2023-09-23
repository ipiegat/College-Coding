from ListMapping import ListMapping


class HashTable:
    def __init__(self):
        self._htsize = 5  # initial size of hash table
        self._buckets_array = [
            ListMapping() for i in range(self._htsize)
        ]  # initialize bucket array of size _htsize
        self._n = 0  # number of items added in map

    def put(self, key, value):
        """put the key-value pair in the right bucket."""
        # Evaluate the address of bucket to hold key-value pair
        bucket = self._get_bucket(key)
        bucket.put(key, value)
        self._n += 1
        if self._n >= len(self._buckets_array):
            self._double()

    def get(self, key):
        """Returns the value associated with key from the right bucket."""
        bucket = self._get_bucket(key)
        return bucket.get(key)

    def _get_bucket(self, key):
        """Returns the right jth bucket depending on key."""
        j = hash(key) % self._htsize
        return self._buckets_array[j]
        # calculate jth index with the help of hash function as discussed in class

    def remove(self, key):
        """Remove the object associated with key."""
        bucket = self._get_bucket(key)
        self._buckets_array.remove(bucket)
        self._htsize -= 1
        self._n -= 1
        # After removing, decrease the size of entries in map

    def _double(self):
        """Doubles the size of hash table."""
        self._htsize *= 2
        old_bucket = self._buckets_array
        # Create a new hash table with size double the original one
        self._buckets_array = [ListMapping() for i in range(self._htsize)]
        # After creating a new double-sized hash table, add the contents
        for e in old_bucket:
            for key, value in e.items():
                bucket = self._get_bucket(key)
                bucket.put(key, value)

        # of original hash table in it.


if __name__ == "__main__":
    HM = HashTable()
    HM.put(1, "one")
    HM.put(2, "two")
    HM.put(3, "three")
    HM.put(4, "four")
    HM.put(5, "five")
    HM.put(6, "six")
    HM.put("ten", 10)

    assert HM.get(2) == "two"
    assert HM.get(4) == "four"
    assert HM.get("ten") == 10
    assert HM.get(6) == "six"

    assert HM._htsize == 10
    assert HM._n == 7
    print("PASSED")
