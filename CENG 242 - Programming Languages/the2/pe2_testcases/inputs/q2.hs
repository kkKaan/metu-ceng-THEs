import PE2

dungeonMap = Node NarrowPassage [] [
    Node UndergroundRiver [Fight (Enemy "Orc" 10 5)] [
        Leaf SlipperyRocks [Fight (Enemy "Necromancer" 30 100)]],
    Node Cavern [Fight (Enemy "Goblins" 5 2), Treasure (Gold 15)] [
        Leaf NarrowPassage [Treasure (Gold 10), Treasure (Potion 5)],
        Leaf UndergroundRiver [Fight (Enemy "Lich" 25 50)],
        Leaf Cavern [Fight (Enemy "Goblins" 5 2),
                     Fight (Enemy "Imp" 4 4),
                     Treasure (Potion 15),
                     Fight (Enemy "Bear" 15 9)]]]

dungeonMap2 = Node NarrowPassage [] [
    Node UndergroundRiver [Fight (Enemy "Orc" 10 5)] [
        Leaf SlipperyRocks [Fight (Enemy "Necromancer" 30 100)]],
    Node Cavern [Fight (Enemy "Goblins" 5 2), Treasure (Gold 15)] [
        Leaf NarrowPassage [Treasure (Gold 10), Treasure (Potion 5)],
        Leaf UndergroundRiver [Fight (Enemy "Lich" 25 50)]]]

gain1 = findMaximumGain 10 dungeonMap
gain2 = findMaximumGain 15 dungeonMap
gain3 = findMaximumGain 50 dungeonMap
gain4 = findMaximumGain 15 dungeonMap2
gain5 = findMaximumGain 40 dungeonMap2

main = do
    putStrLn (show gain1)
    putStrLn (show gain2)
    putStrLn (show gain3)
    putStrLn (show gain4)
    putStrLn (show gain5)