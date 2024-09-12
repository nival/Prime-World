from os import path
import MigratorsFramework as MF

def get_variable_string(forest):
    if len(forest) == 0:
        return '-missing-'
    elif len(forest) > 1:
        return '-multiple-'

    tree = forest[0]
    value = tree['sString']
    return value[0].data

def is_zero(value):
    return value == '0' or value == '0.0f' or value == '-missing-'

def first(forest):
    return forest[0] if len(forest) > 0 else None

class PrintFields:
    def __call__(self, tree):
        print get_variable_string(tree['aoeRadius']) + ', ' + get_variable_string(tree['aoeAngle']) + ', ' + get_variable_string(tree['aoeWidth']) + ', ' + get_variable_string(tree['useRange'])
        return tree

class AddFields:
    def __call__(self, tree):
        rtree = tree['aoeRadius']
        rzero = is_zero(get_variable_string(rtree))
        atree = tree['aoeAngle']
        azero = is_zero(get_variable_string(atree))
        wtree = tree['aoeWidth']
        wzero = is_zero(get_variable_string(wtree))

        print get_variable_string(rtree) + ', ' + get_variable_string(atree) + ', ' + get_variable_string(wtree) + ', ' + get_variable_string(tree['useRange'])
        print rzero
        print azero
        print wzero

        # choose the one to copy from
        if azero and wzero:
            if rzero:
                aoeType = 'None'
                source = first(rtree)
            else:
                aoeType = 'Disk'
                source = first(rtree)
        elif not azero:
            # assert(wzero)
            # assert(radius == range) # failed for Fire Fox
            aoeType = 'Cone'
            source = first(atree)
        else:
            # assert(not wzero)
            aoeType = 'Corridor'
            source = first(wtree)

        # add type
        if len(tree['aoeType']) == 0:
            new_node = MF.Node('aoeType')
            new_node.data = aoeType;
            tree['aoeType'] = new_node

        # add size
        if len(tree['aoeSize']) == 0:
            new_node = MF.Node('aoeSize')
            if source:
                new_node.attrs = source.attrs;
                new_node.children = source.children;
                new_node.data = source.data;
            tree['aoeSize'] = new_node

        print "===>", aoeType
        return tree

def main():
    # http://SITE

    # job = PrintFields()
    job = AddFields()
    MF.run([
      "Ability",
      "BaseAttack",
      "Consumable",
      "Glyph",
      "Talent"
      ], job)

    print "done"

if __name__ == "__main__":
    main()
