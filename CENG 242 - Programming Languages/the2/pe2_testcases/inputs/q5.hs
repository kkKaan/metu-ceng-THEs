import PE2

dungeonMap = EmptyTree

dungeonMap2 = Leaf Cavern [Fight (Enemy "Zombie" 5 10)]

dungeonMap3 = Node NarrowPassage [Treasure (Gold 10)] [
    Node UndergroundRiver [Fight (Enemy "Orc" 10 5)] [
        Leaf SlipperyRocks [Fight (Enemy "Necromancer" 30 100)]],
    Node Cavern [Fight (Enemy "Goblins" 5 2)] [
        Leaf UndergroundRiver [Fight (Enemy "Lich" 25 50)]]]

dungeonMap4 = Node NarrowPassage [Treasure (Gold 10)] [
    Node UndergroundRiver [Fight (Enemy "Orc" 10 5)] [
        Leaf SlipperyRocks [Fight (Enemy "Necromancer" 30 100)]],
    Node Cavern [Fight (Enemy "Goblins" 5 2), Treasure (Gold 15)] [
        Leaf UndergroundRiver [Fight (Enemy "Lich" 25 50)],
        Leaf Cavern [Fight (Enemy "Goblins" 5 2),
                     Fight (Enemy "Imp" 4 4),
                     Treasure (Potion 15),
                     Fight (Enemy "Bear" 15 9)]]]

dungeonMap5 = Node NarrowPassage [Treasure (Gold 10)] [
    Node UndergroundRiver [Fight (Enemy "Orc" 10 5)] [
        Leaf SlipperyRocks [Fight (Enemy "Necromancer" 30 100)]],
    Node Cavern [Fight (Enemy "Goblins" 5 2), Treasure (Gold 15)] [
        Leaf NarrowPassage [Treasure (Gold 10), Treasure (Potion 5)],
        Leaf UndergroundRiver [Fight (Enemy "Lich" 25 50)],
        Leaf Cavern [Fight (Enemy "Goblins" 5 2),
                     Fight (Enemy "Imp" 4 4),
                     Treasure (Potion 15),
                     Fight (Enemy "Bear" 15 9)]]]
 
st1 = mostEfficientSubtree dungeonMap
st2 = mostEfficientSubtree dungeonMap2
st3 = mostEfficientSubtree dungeonMap3
st4 = mostEfficientSubtree dungeonMap4
st5 = mostEfficientSubtree dungeonMap5

main = do
    putStrLn (show st1)
    putStrLn (show st2)
    putStrLn (show st3)
    putStrLn (show st4)
    putStrLn (show st5)
