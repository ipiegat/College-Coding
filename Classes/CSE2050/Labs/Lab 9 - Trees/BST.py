class BSTNode:
    def __init__(self, data, parent=None):
        self.data = data
        self.parent = parent
        self.left = None
        self.right = None


class BinarySearchTree:
    def __init__(self):
        self.root = None

    ################ Task 1 ################
    def insert(self, data):
        if self.root is None:
            self.root = BSTNode(data)

        else:
            self._add_child(data, self.root)
        # use helper _add_child method to add children to existing parent

    def _add_child(self, data, p_node):
        if data == p_node.data:  # duplicate items cannot be added
            return

        if data == p_node.data:
            print("duplicates not alowed")
            return

        if data < p_node.data:
            if p_node.left:
                self._add_child(data, p_node.left)

            else:
                p_node.left = BSTNode(data, p_node)

        else:
            if p_node.right:
                self._add_child(data, p_node.right)
            else:
                p_node.right = BSTNode(data, p_node)
        # implement logic to recursively add a node at appropriate location

    def get_max(self):
        # retrieve the appropriate node with the help of
        # helper method _get_right_child
        if self.root:
            return self._get_right_child(self.root)
        else:
            return None

    def _get_right_child(self, node):
        # helper method to retrieve right node recursively
        if node.right:
            return self._get_right_child(node.right)

        return node.data

    def get_min(self):
        # retrieve the appropriate node with the help of
        # helper method _get_left_child
        if self.root:
            return self._get_left_child(self.root)
        else:
            return None

    def _get_left_child(self, node):
        # helper method to retrieve left node recursively
        if node.left:
            return self._get_left_child(node.left)

        return node.data

    def traverse_in_order(self, node):
        traversed_data = []
        if node:
            traversed_data = self.traverse_in_order(node.left)
            traversed_data.append(node.data)
            traversed_data = traversed_data + self.traverse_in_order(node.right)

        return traversed_data

        # traverse the tree in in-order fashion and keep
        # adding the elements in the traversed_data list

    def delete(self, data):
        # starting from root node, pass the data and node
        # to be deleted to the helper node _remove_node
        if self.root:
            self._remove_node(data, self.root)

    def _remove_node(self, data, node):
        # remove the specified node
        # separate cases for deleting leaf node, node with one child and
        # node with two children

        # For deleting root node with two children, use the
        # helper method _get_predecessor to get the predecessor
        if node is None:
            return

        if data < node.data:
            self._remove_node(data, node.left)
        elif data > node.data:
            self._remove_node(data, node.right)
        else:  # once the required node to be deleted is foudn
            if node.left is None and node.right is None:
                print(f"Removing a leaf node with data: {node.data}")
                parent = node.parent

                if parent is not None:
                    if parent.right == node:
                        parent.right = None
                    if parent.left == node:
                        parent.left = None
                else:  # if the element we are removing is root
                    self.root = None

                del node

            elif node.left is None and node.right is not None:
                print(f"Removing node having a right child with data: {node.data}")
                parent = node.parent

                if parent is not None:
                    if parent.right == node:
                        parent.right = node.right
                    if parent.left == node:
                        parent.left = node.right
                else:
                    self.root = node.right

                node.right.parent = parent

                del node

            elif node.left is None and node.right is None:
                print(f"Removing node having a left child with data: {node.data}")
                parent = node.parent

                if parent is not None:
                    if parent.right == node:
                        parent.right = node.left
                    if parent.left == node:
                        parent.left = node.left
                else:
                    self.root = node.left

                node.left.parent = parent

                del node

            else:  # when both children are present
                print(
                    f"Removing node having the left child ({node.left.data}) / and right child({node.right.data})"
                )

                predecessor = self._get_predecessor(node.left)
                print("predecessor before: ", predecessor.data)
                predecessor.data, node.data = node.data, predecessor.data
                print("precessor after: ", predecessor.data)
                self._remove_node(data, predecessor)

    def _get_predecessor(self, node):
        if node.right:
            return self._get_predecessor(node.right)

        return node

    ################ Task 2 ################
    def traverse_pre_order(self, node):
        # traverse the tree in pre-order fashion and keep
        # adding the elements in the traversed_data list
        traversed_data = []
        if node:
            traversed_data.append(node.data)
            traversed_data = traversed_data + self.traverse_pre_order(node.left)
            traversed_data = traversed_data + self.traverse_pre_order(node.right)

        return traversed_data

    def traverse_post_order(self, node):
        # traverse the tree in post-order fashion and keep
        # adding the elements in the traversed_data list
        traversed_data = []
        if node:
            traversed_data = self.traverse_post_order(node.left)
            traversed_data = traversed_data + self.traverse_post_order(node.right)
            traversed_data.append(node.data)

        return traversed_data


if __name__ == "__main__":
    BST = BinarySearchTree()

    random_data = [12, 4, 20, 8, 1, 16, 27]
    for data in random_data:
        BST.insert(data)

    print("Testing Max...")
    assert BST.get_max() == 27
    print("PASSED!")

    print()
    print("Testing Min...")
    assert BST.get_min() == 1
    print("PASSED!")

    print()
    print("Testing In-order Traversal...")
    traversed_data = BST.traverse_in_order(BST.root)
    assert traversed_data == [1, 4, 8, 12, 16, 20, 27]
    print("PASSED!")

    print()
    print("Testing Deletion of root node with two child...")
    BST.delete(12)
    traversed_data = BST.traverse_in_order(BST.root)
    assert traversed_data == [1, 4, 8, 16, 20, 27]
    print("PASSED!")

    print()
    print("Checking new root after deletion...")
    assert BST.root.data == 8
    print("VERIFIED!")

    ########## Task2 ##########
    print()
    print("########## Task 2 ##########")
    BST2 = BinarySearchTree()
    #            12
    #       4         20
    #     1   8    16   27
    random_data = [12, 4, 20, 8, 1, 16, 27]
    for data in random_data:
        BST2.insert(data)

    print()
    print("Testing Pre-order Traversal...")
    traversed_data = BST2.traverse_pre_order(BST2.root)
    assert traversed_data == [12, 4, 1, 8, 20, 16, 27]
    print("PASSED!")

    print()
    print("Testing Post-order Traversal...")
    traversed_data = BST2.traverse_post_order(BST2.root)
    assert traversed_data == [1, 8, 4, 16, 27, 20, 12]
    print("PASSED!")
