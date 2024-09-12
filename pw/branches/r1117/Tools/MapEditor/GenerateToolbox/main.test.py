import unittest

import main


class Test(unittest.TestCase):

    def test(self):
        self.check('Building', 'Resources/Chest.RSRC', ('Resources', 'Chest'))
        self.check('Building', 'Test/SpeedTree/Tree', ('SpeedTree', 'Tree'))
        self.check('ArtifactResource', 'Artifacts/BreathOfAsha/ArtifactResource', ('Artifacts', 'BreathOfAsha'))
        self.check('Building', 'Buildings/CaveTunnel/Building', ('Buildings', 'CaveTunnel'))
        self.check('Building', 'Buildings/Teleport', ('Buildings', 'Teleport'))
        self.check('Creature', 'Creatures/Haven/T1_Sentinel/_.Creature', ('Haven', 'T1_Sentinel'))
        self.check('Town', 'Towns/Haven/Town', ('Towns', 'Haven'))
        self.check('Building', 'Terrain/Flora/BigTrees/Elm/_01.GMOB', ('BigTrees', 'Elm_01'))
        self.check('Building', 'Terrain/Lakes/Lake_01.GMOB', ('Lakes', 'Lake_01'))
        self.check('Building', 'Terrain/Stuff/NecropolisRocks/NecropolisRock_01', ('NecropolisRocks', 'NecropolisRock_01'))
        self.check('Building', 'Terrain/Stuff/Stones/Stone_01', ('Stones', 'Stone_01'))
        self.check('Building', 'Buildings/SacrificialPlace/SacrificialPlace', ('Buildings', 'SacrificialPlace'))
        
    def _test_Exclusive(self):        
        self.check('Teleport', 'Buildings/CaveTunnel/Building', ('Buildings', 'CaveTunnel'))
        
    def check(self, tag_name, path, (expected_category, expected_name)):
        _tokens = path.split('/')
        head = _tokens[-1]
        tokens = _tokens[:-1]
        c = main.ComplexConverter(tag_name, tag_name)
        category, name = c.do(tokens, head)
        self.assertEquals(expected_category, category)
        self.assertEquals(expected_name, name)
        
unittest.main()        
