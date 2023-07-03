import PE2

dungeonMap = EmptyTree

dungeonMap2 = Leaf Cavern [Fight (Enemy "Zombie" 5 10)]

dungeonMap3 = Node NarrowPassage [Treasure (Gold 10)] [
    Node UndergroundRiver [Fight (Enemy "Orc" 10 5)] [
        Leaf SlipperyRocks [Fight (Enemy "Necromancer" 30 100)]],
    Node Cavern [Fight (Enemy "Goblins" 5 2)] [
        Leaf UndergroundRiver [Fight (Enemy "Lich" 25 50)]]]

pair1 = mostDistantPair 20 dungeonMap
pair2 = mostDistantPair 20 dungeonMap2
pair3 = mostDistantPair 15 dungeonMap3
pair4 = mostDistantPair 35 dungeonMap3
pair5 = mostDistantPair 45 dungeonMap3

main = do
    putStrLn (show pair1)
    putStrLn (show pair2)
    putStrLn (show pair3)
    putStrLn (show pair4)
    putStrLn (show pair5)
