from os import path
import MigratorsFramework as MF

class AddNewField:
    def __init__(self, field, value):
        self.field = field
        self.value = value

    def __call__(self, tree):
        if 0 == len(tree[self.field]):
            new_node                = MF.Node(self.field)
            new_node.data           = self.value;
            tree[self.field]        = new_node
        return tree;

def main():
    # http:/SITE
    addOpaque = AddNewField("opaque", "true")
    MF.run("TreeObject", addOpaque, MF.dataPath('Terrain/Trees/Test'))

    print "done"

if __name__ == "__main__":
    main()
