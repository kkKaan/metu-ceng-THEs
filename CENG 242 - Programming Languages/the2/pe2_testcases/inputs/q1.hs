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

path1 = traversePath 50 dungeonMap [0, 0]
path2 = traversePath 15 dungeonMap [1, 0]
path3 = traversePath 40 dungeonMap [1, 1]
path4 = traversePath 15 dungeonMap [1, 2]

main = do
    putStrLn (show path1)
    putStrLn (show path2)
    putStrLn (show path3)
    putStrLn (show path4)
