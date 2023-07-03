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

paths1 = findViablePaths 5 dungeonMap
paths2 = findViablePaths 10 dungeonMap
paths3 = findViablePaths 15 dungeonMap
paths4 = findViablePaths 35 dungeonMap
paths5 = findViablePaths 50 dungeonMap

main = do
    putStrLn (show paths1)
    putStrLn (show paths2)
    putStrLn (show paths3)
    putStrLn (show paths4)
    putStrLn (show paths5)
