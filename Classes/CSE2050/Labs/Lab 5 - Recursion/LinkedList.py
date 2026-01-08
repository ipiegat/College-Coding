class _Node:
    def __init__(self, element, next):
        self._element = element
        self._next = next

class LinkedList:
    def __init__(self):
        self._head = None
        self._size = 0

    def __len__(self):          #Returns the number of elements in Linked List
        return self._size


    def insert_at_head(self, element):
        """ Insert element at Head. """
        #See slide#38 Week-4-2050.pdf on HuskyCT. All the steps are done in two lines here
        self._head = _Node(element, self._head)
        self._size +=1

    def remove_from_head(self):
        """ Delete element from Head. """

        if len(self) == 0:
            raise Exception("Attempt to remove from empty linked list")
        else:
            read_element = self._head._element      #Reading element before detaching/deleting it from LL.
            #See slide#41 Week-4-2050.pdf on HuskyCT.
            #Updating the "next node of current head of LL" to be set as the new head of the updated LL.
            self._head = self._head._next
            self._size -= 1
            return read_element

    def __str__(self):
        """ Overriding builtin __str__ method for demonstration. """
        if len(self) == 0:
            return ''

        list_of_strings = []
        self._str(self._head, list_of_strings)
        return ''.join(list_of_strings)

    # leading underscore - this is private!
    # attributes within this class, like __str__, can call it, but users should not
    # this is called a "helper" function
    def _str(self, node, list_of_strings):
        if node._next is None:                          # base case: tail node
            list_of_strings.append(str(node._element))  # add this item to the list of strings
            return                                      # start bouncing back up chain of recursive calls

        else:                                           # non-base case: recursively call on next node
            self._str(node._next, list_of_strings)              # recursively call on next node

        # Now that we have hit the tail, and are bouncing back up.
        # add this item to "list_of_strings", then return
        list_of_strings.insert(0, str(node._element) + "-")    # pre-pend "item-" to list of strings

    ####################################################################
    # Lab Task 1: Override built-in method "in"
    # write __contains__ method and recursively call _contains helper method to
    # check all the elements in the linked list
    def __contains__(self,element):
        if self._head == None:
            return False
        
        if element == self._head._element:
            return True
        
        return self._contains(self._head, element)

    def _contains(self, node, element):
        if node == None:
            return False
        
        if element == node._element:
            return True
        
        if node != None:
            return self._contains(node._next, element)


    # Lab Task 2: add element at the tail by traversing the list recursively to
    # determine the tail element and then add the new node
    def insert_at_tail(self, element):
        if self._size == 0:
            self._head = _Node(element, None)
            self._size += 1
 
        elif self._size == 1:
            self._head._next = _Node(element, None)
            self._size += 1
        else:
            self._size += 1
            return self._add_at_tail(self._head, element)
    
    def _add_at_tail(self, node, element):
        if node._next == None:
            node._next = _Node(element, None)
        else:
            return self._add_at_tail(node._next, element)
        
 
     ####################################################################
if __name__ == '__main__':
    n = _Node(1, None)
    assert n._element == 1
    assert n._next is None
    print("Node tests pass")

    # Test LL - add_first/len/remove_first
    LL = LinkedList()

    for i in range(4):
        assert len(LL) == i
        LL.insert_at_head(i)

    for i in range(4):
        assert LL.remove_from_head() == 3-i
        assert len(LL) == 3-i

    # # Test LL - str
    for i in range(4):
        LL.insert_at_head(i)

    assert str(LL) == "3-2-1-0"
    print("starter LL tests pass!")

    ####################################################################
    #Testing Lab task 1
    LL = LinkedList()
    for i in range(4):
        LL.insert_at_head(i)

    assert 3 in LL
    assert not 4 in LL
    print("in tests work!")

    #Testing Lab task 2 and 1 together
    LL = LinkedList()
    for i in range(4):
        LL.insert_at_tail(i)

    print(str(LL))
    assert str(LL) == "0-1-2-3"
    assert 3 in LL
    assert not 4 in LL

    for i in range(4):
        assert LL.remove_from_head() == i
    print("remove_from_head tests work!")

    ####################################################################
