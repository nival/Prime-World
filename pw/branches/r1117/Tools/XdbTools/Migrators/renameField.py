from os import path
import MigratorsFramework as MF

class RenameField:
    def __init__(self, oldfield, newfield):
        self.oldfield = oldfield
        self.newfield = newfield

    def __call__(self, tree):
        subtrees = tree[self.oldfield]
        if len(subtrees) != 0:
            for subtree in subtrees:
                new_node = MF.Node(self.newfield)
                new_node.attrs = subtree.attrs;
                new_node.children = subtree.children;
                new_node.data = subtree.data;
                tree[self.newfield] = new_node
            del tree[self.oldfield]
        return tree;

def main():
    # http://SITE
    renameField = RenameField("color", "colorMul")
    MF.run("ScaleColorEffect", renameField, MF.defaultDataPath())

    print "done"

if __name__ == "__main__":
    main()
