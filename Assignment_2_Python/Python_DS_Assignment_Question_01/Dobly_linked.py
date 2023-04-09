class _DoubleLinkedBase:

    class _Node:
        __slots__ = ['_element', '_prev', '_next'] 

        def __init__(self, element, prev, next): 
            self._element = element
            self._prev = prev
            self._next = next

    def __init__(self):
        """Create an empty list"""
        self._header = self._Node(None, None, None)
        self._trailer = self._Node(None, None, None)
        self._header._next = self._trailer
        self._trailer._prev = self._header
        self._size = 0

    def __len__(self):
        """Return the number of elements in the list"""
        return self._size

    def is_empty(self):
        """Return true if list is empty"""
        if self._header._next==self._trailer:
            return True
        else:
            return False

    def _insert_between(self, e, predecessor, successor):
        """Add element e between two existing nodes and return new node"""
        newest = self._Node(e, predecessor, successor)
        predecessor._next=newest
        successor._prev=newest
        self._size += 1
        

    def _delete_node(self, node):
        """Delete nonsentinel node from the list and return its elements"""
        pre = node._prev
        nex= node._next
        temp = node._element
        del node
        pre._next=nex
        nex._prev=pre
        self._size -= 1
        return temp

if __name__=="__main__":
    temp = _DoubleLinkedBase()  #initialising class
    print("if link list is empty=",temp.is_empty())   # printing whether list is empty or not
    print("length of link list =",temp.__len__())   # printing lenght of list
    temp._insert_between(4,temp._header,temp._trailer)  # inserting element between header and trailer and printing returning object 
    temp._insert_between(4,temp._header,temp._trailer)  # inserting element between header and trailer and printing returning object 
    print( "is link list empty =",temp.is_empty())  # printing whether list is empty or not
    print("length of link list =",temp.__len__())   # printing lenght of list
    temp._insert_between(5,temp._header._next,temp._trailer) # inserting element between header._next and trailer and printing returning object
#     print( "is link list empty =",temp.is_empty())  # printing whether list is empty or not
#     print("length of link list =",temp.__len__())   # printing lenght of list
    print(temp._header._next._element,temp._trailer._prev._element) # printing inserted two elements
    # print(temp._delete_node(temp._header._next))    # deleting header._next and printing its return value
#     print( "is link list empty =",temp.is_empty())  # printing whether list is empty or not
    # print("length of link list =",temp.__len__())   # printing lenght of list